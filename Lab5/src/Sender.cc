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

#include "Sender.h"
#include <bitset>

Define_Module(Sender);

void Sender::initialize()
{
    scheduleAt(0, new cMessage("'"));
}

void Sender::handleMessage(cMessage *msg)
{
    //Define message of type MyMessage_Base
    MyMessage_Base *message = new MyMessage_Base();

    //Get the message from the user
    std::string M_Payload;
    std::cout << "Enter a string ";
    std::getline(std::cin, M_Payload);
    EV << "Payload:\n" << M_Payload << "\n";

    message -> setM_Type(2);

    //Generate bitstream of the string
    std::string bitstream;
    for (char c : M_Payload) {
        bitstream += std::bitset<8>(c).to_string();
    }
    EV << "Original Bitstream:\n" << bitstream << "\n";

    // Frame header (character count)
    int charCount = M_Payload.length() + 2;
    char M_Header = (char)charCount;
    message -> setM_Header(M_Header);
    EV << "charCount:\n" << std::bitset<8>(charCount).to_string() << "\n";

    // Calculate parity (XOR of all characters)
    std::bitset<8> parity(0);
    for (char c : M_Payload) {
        parity ^= std::bitset<8>(c);
    }
    std::bitset<8> charCountBits(charCount);
    parity ^= charCountBits;
    EV << "parity:\n" << parity.to_string() << "\n";

    message -> setM_Trailer((char) parity.to_ulong());

    // Introduce a single bit error with 50% probability
    volatile float val = uniform(0, 1);
    EV << "Random value: " << val << endl;

    if (val <= 0.5) {
        volatile int errorBit = intuniform(0, bitstream.length() - 1);
        bitstream[errorBit] = (bitstream[errorBit] == '0') ? '1' : '0';
        EV << "Single bit error introduced at bit " << errorBit << "\n";
        EV << "Bitstream after error:\n" << bitstream << "\n";
        EV << "************************************************" << "\n";
        //Regenerate the string
        std::string regeneratedString;
        for (size_t i = 0; i < bitstream.size(); i += 8) {
            std::bitset<8> bits(bitstream.substr(i, 8));
            regeneratedString += char(bits.to_ulong());
        }
        message -> setM_Payload(regeneratedString.c_str());
    }
    else
    {
        EV << "No error generated" << "\n";
        EV << "************************************************" << "\n";
        message -> setM_Payload(M_Payload.c_str());
    }

    //Send the messsage
    send(message, "out");
}
