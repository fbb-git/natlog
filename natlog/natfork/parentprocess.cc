#include "natfork.ih"

    // only called from NarFork::fork, starting a daemon by ending the 
    // the main program.
void NatFork::parentProcess()
{
    d_pipe.readFrom(STDIN_FILENO);

    Selector selector;
    selector.addReadFd(STDIN_FILENO);
    selector.setAlarm(0, 500000);           // wait for max. 1/2 second

    selector.wait();
    if (selector.nReady())
    {
        string line;
        getline(cin, line);
        fmsg << line << endl;
    }

    ofstream pidFile(Options::instance().pidFile());
    pidFile << pid() << endl;

    throw 0;
}
