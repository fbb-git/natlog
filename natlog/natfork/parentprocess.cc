#include "natfork.ih"

    // only called by NarFork::fork, starting a daemon by ending 
    // the main program.

void NatFork::parentProcess()
{
    d_pipe.readFrom(STDIN_FILENO);

        // if the child process puts a message in the pipe then the child 
        // could not continue, and the parent returns 1.
    Selector selector;
    selector.addReadFd(STDIN_FILENO);
    selector.setAlarm(0, 500000);           // wait for max. 1/2 second

    selector.wait();
    if (selector.nReady())
    {
        string line;
        getline(cin, line);                 // get the child's dying message
        fmsg << line << endl;
    }

        // the daemon started OK, now write its pid-file:
    ofstream pidFile(Options::instance().pidFile());
    pidFile << pid() << endl;

    throw 0;
}





