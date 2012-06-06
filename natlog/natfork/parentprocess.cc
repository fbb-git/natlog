#include "natfork.ih"

    // only called from NarFork::fork, starting a daemon by ending the 
    // the main program.
void NatFork::parentProcess()
{
    throw 0;
}
