#include "natfork.ih"

void NatFork::childProcess()
{
    ShowSeconds::setFormat();

    if (d_options.daemon())
        prepareDaemon();

    try
    {
        if (d_mode == CONNTRACK)
        {
            Conntrack conntrack(d_stdMsg);
            conntrack.run();
        }
        else 
        {
            Devices devices(d_stdMsg);
            devices.run();
        }
    }
    catch (exception const &err)        // errors at Conntrack or Devices
    {
        if (not d_options.daemon())
            throw;                      // rethrow the exception

        d_stdMsg << err.what() << endl;
//        out << 1 << endl;               // The daemon can't start:
                                        // inform via the pipe
    }

        // when the child process ends it throws away its own pid file:
    ifstream pidFile(d_options.pidFile());
    pid_t pid;
    if (pidFile >> pid && pid == getpid())
    {
        pidFile.close();
        unlink(d_options.pidFile().c_str());
    }

    throw Options::OK;              // ends the program or the child process
}







