package lab5;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=405,225");
    submodules:
        sender: Sender {
            @display("p=86,92");
        }
        receiver: Reciever {
            @display("p=238,92");
        }
    connections:
        sender.out --> receiver.in;
        receiver.out --> sender.in;
}