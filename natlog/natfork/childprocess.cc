#include "natfork.ih"

void NatFork::childProcess()
{
    ShowSeconds::setFormat();

    if (d_options.daemon())
        prepareDaemon();

    OFdStream out(d_pipe.writeFd());        // the message to the parent

    try
    {
        if (d_mode == CONNTRACK)
        {
            Conntrack conntrack(d_stdMsg);
            conntrack.run(out);
        }
        else 
        {
            Devices devices(d_stdMsg);
            devices.run(out);
        }
    }
    catch (Errno const &err)            // any errors at Conntrack or Devices
    {                                   // are thrown as Errno exceptions
        if (not d_options.daemon())
            throw;                      // rethrow the exception

        d_stdMsg << err.why() << endl;
        out << 1 << endl;               // The daemon can't start:
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







