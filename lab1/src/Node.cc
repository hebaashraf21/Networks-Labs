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

#include "Node.h"
#include <string>

Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body
    if(strcmp(getName(),"Tic")==0)
    {
        cMessage *msg = new cMessage("Tic_0");
        send(msg,"out");
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    static int counter = 0;
    counter++;

    if (counter <= 9)
    {
        std::string message;
        if(counter % 2 == 0)
        {
            message = "Tic_" + std::to_string(counter);
        }
        else
        {
            message = "Toc_" + std::to_string(counter);
        }

        cMessage *newMsg = new cMessage(message.c_str());
        send(newMsg, "out");
    }

    delete msg;
}
