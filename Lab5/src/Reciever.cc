//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Reciever.h"
#include <bitset>

Define_Module(Reciever);

void Reciever::initialize()
{
    // TODO - Generated method body
}

void Reciever::handleMessage(cMessage *msg)
{
    //Cast the recieved message
    MyMessage_Base *mmsg = check_and_cast<MyMessage_Base *>(msg);

    // Extract the received bitstream from the message
    std::string payload = mmsg ->getM_Payload();
    std::string receivedBitstream;
    //Variable to perform XOR
    std::bitset<8> result(0);
    for (char c : payload) {
        receivedBitstream += std::bitset<8>(c).to_string();
        std::bitset<8> binaryGroup(c);
        // Perform XOR operation on the binary representations of the payload
        result ^= binaryGroup;
       }
    EV << "Received Message Bitstream:\n" << receivedBitstream << "\n";

    //Convert header and trailer to butstream
    std::bitset<8> charCountBits(mmsg -> getM_Header());
    std::bitset<8> parityBits(mmsg -> getM_Trailer());
    // Perform XOR operation on the binary representations of the char count and parity
    result ^= charCountBits;
    result ^= parityBits;

    if (result.to_ulong() == 0) {
        EV << "No error detected.\n";
        EV << "The original message is: " << mmsg ->getM_Payload() << "\n";
        mmsg -> setM_Type(1);
        EV << "Akc sent: " << mmsg ->getM_Type() << "\n";
    } else {
        EV << "Error detected in received bitstream.\n";
        mmsg -> setM_Type(0);
        EV << "NON_Akc sent: " << mmsg ->getM_Type() << "\n";
    }
    //Send the messsage
    send(mmsg, "out");
}
