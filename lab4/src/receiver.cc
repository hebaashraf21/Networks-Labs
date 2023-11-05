#include "receiver.h"
#include <bitset>

Define_Module(Receiver);

void Receiver::initialize()
{

}

void Receiver::handleMessage(cMessage *msg)
{
    // Extract the received bitstream from the message
    std::string receivedBitstream = msg->getName();
    EV << "Received Bitstream:\n" << receivedBitstream << "\n";

    // Divide the received bitstream into groups of 8 bits
    std::vector<std::string> byteGroups;
    for (size_t i = 0; i < receivedBitstream.length(); i += 8) {
        byteGroups.push_back(receivedBitstream.substr(i, 8));
    }

    // Perform XOR operation on the binary representations
    std::bitset<8> result(0);
    for (const std::string& group : byteGroups) {
        std::bitset<8> binaryGroup(group);
        result ^= binaryGroup;
    }

    if (result.to_ulong() == 0) {
        EV << "No error detected.\n";

        // Extract original bitstream
        std::string originalBitstream = receivedBitstream.substr(8, receivedBitstream.length() - 16);

        // Convert original bitstream to message
        std::string originalMessage = "";
        for (size_t i = 0; i < originalBitstream.length(); i += 8) {
            std::bitset<8> byte(originalBitstream.substr(i, 8));
            char c = char(byte.to_ulong());
            originalMessage += c;
        }

        EV << "The original message is: " << originalMessage << "\n";


    } else {
        EV << "Error detected in received bitstream.\n";

    }

    delete msg;
}
