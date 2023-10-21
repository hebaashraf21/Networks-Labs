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

#include "Hub.h"

Define_Module(Hub);

void Hub::initialize()
{
    int N = getParentModule()->par("N");
    int randomNode = intuniform(0, N-1);
    cMessage *helloMsg = new cMessage("Hello from Hub");
    send(helloMsg, "out", randomNode);
}

void Hub::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        int N = getParentModule()->par("N");
        int randomNode = intuniform(0, N-1);
        cMessage *helloMsg = new cMessage("Hello from Hub");
        send(helloMsg, "out", randomNode);

    }
    else
    {
        double interval = exponential(2.0);
        cMessage *selfMsg = new cMessage("Self Message");
        scheduleAt(simTime() + interval, selfMsg);
    }
}
