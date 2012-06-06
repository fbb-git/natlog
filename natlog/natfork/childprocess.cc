#include "natfork.ih"

void NatFork::childProcess()
{
    Conntrack conntrack;

    conntrack.run();

    throw 0;                    // ends the program or the child process
}
