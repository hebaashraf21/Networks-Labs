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

Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method bodys
    EV << "Starting Node" << getIndex() << endl;
    if(getIndex()==0){
        cMessage *msg = new cMessage ("");
        msg -> setKind(1);
        send(msg, "out");
    }

}

void Node::handleMessage(cMessage *msg)
{
    if(getIndex()==0){
        EV << "N = " << msg -> getKind() << endl;
        cancelAndDelete(msg);
        }
    else{
        msg -> setKind(msg -> getKind() + 1);
        send(msg, "out");
    }
}
