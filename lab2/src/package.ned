package lab2;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=415,212");
    submodules:
        player1: Player1 {
            @display("p=98,82");
        }
        player2: Player2 {
            @display("p=237,82");
        }
    connections:
        player1.out --> player2.in;
        player2.out --> player1.in;
}

