#include "natfork.ih"

    // only called by NarFork::fork, starting a daemon by ending 
    // the main program.

void NatFork::parentProcess()
{
        // write the daemon's pid-file:
    ofstream pidFile(Options::instance().pidFile());
    pidFile << pid() << endl;

    throw Options::OK;
}





