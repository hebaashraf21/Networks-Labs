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

#include "player2.h"

Define_Module(Player2);

void Player2::initialize()
{
}

void Player2::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "Guess the number") == 0 || strcmp(msg->getName(), "Wrong Guess!") == 0)
    {
        int guess = par("guessNumber").intValue();
        EV << "Player2's Guess: " << guess << endl;

        msg->setName("Guess");
        msg->addPar("guess");
        msg->par("guess").setLongValue(guess);
        send(msg, "out");
    }

}

