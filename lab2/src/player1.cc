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


#include "player1.h"

Define_Module(Player1);

void Player1::initialize()
{
    //int secretNumber = par("secretNumber").intValue();
    EV << "Secret number is: " << par("secretNumber").intValue() << endl;

    cMessage *msg = new cMessage("Guess the number");
    send(msg, "out");
}

void Player1::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "Guess") == 0)
    {
        int guess = int(msg->par("guess").longValue());
        if (guess == par("secretNumber").intValue())
        {
            EV << "Player2 made a correct guess!" << endl;
            msg->setName("Correct Guess!");
            send(msg, "out");
            endSimulation();
        }
        else
        {
            EV << "Player2 made a wrong guess!" << endl;
            msg->setName("Wrong Guess!");
            send(msg, "out");
        }
    }
    else
    {
        delete msg;
    }
}


