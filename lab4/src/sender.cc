#include <bitset>
#include "sender.h"
#include <ctime>

Define_Module(Sender);

void Sender::initialize()
{
    while (true) {
        std::string input;
        std::cout << "Enter a string (or type 'q' to quit): ";
        std::getline(std::cin, input);

        if (input == "q") {
            break;
        }

        std::string bitstream;
        for (char c : input) {
            bitstream += std::bitset<8>(c).to_string();
        }
        EV << "Original Bitstream:\n" << bitstream << "\n";

        // Add frame header (character count)
        int charCount = input.length() + 2;
        bitstream = std::bitset<8>(charCount).to_string() + bitstream;

        // Calculate parity (XOR of all characters)
        std::bitset<8> parity(0);
        for (char c : input) {
            parity ^= std::bitset<8>(c);
        }
        std::bitset<8> charCountBits(charCount);
        parity ^= charCountBits;

        // Add frame trailer (parity byte)
        bitstream += std::bitset<8>(parity).to_string();

        EV << "Bitstream after header and trailer:\n" << bitstream << "\n";

        // Introduce a single bit error with 50% probability
        volatile float val = uniform(0, 1);
        EV << "Random value: " << val << endl;

        if (val <= 0.5) {
            volatile int errorBit = intuniform(0, bitstream.length() - 1);
            bitstream[errorBit] = (bitstream[errorBit] == '0') ? '1' : '0';
            EV << "Single bit error introduced at bit " << errorBit << "\n";
            EV << "Bitstream after header, error, and trailer:\n" << bitstream << "\n";
            EV << "************************************************" << "\n";
        }
        else
        {
            EV << "No error generated" << "\n";
            EV << "************************************************" << "\n";
        }


        cMessage *message = new cMessage();
        message->setName(bitstream.c_str());
        send(message, "out");
    }
}




void Sender::handleMessage(cMessage *msg)
{

}
