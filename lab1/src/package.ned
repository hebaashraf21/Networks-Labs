package lab1;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=453,242");
    submodules:
        Tic: Node {
            @display("p=98,103");
        }
        Toc: Node {
            @display("p=215,103");
        }
    connections:
        Tic.out --> Toc.in;
        Toc.out --> Tic.in;
}

