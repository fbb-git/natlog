#include "natfork.ih"

void NatFork::childProcess()
{
    Options &options(Options::instance());

    ShowSeconds::setFormat(options.time());

    if (options.daemon())
        prepareDaemon();

    OFdStream out(d_pipe.writeFd());
    try
    {
        if (d_mode == CONNTRACK)
        {
            Conntrack conntrack(d_out);
            conntrack.run(out);
        }
        else 
        {
            Devices devices(d_out);
            devices.run(out);
        }
    }
    catch (Errno const &err)
    {
        out << err.why() << endl;
    }

    ifstream pidFile(options.pidFile());
    pid_t pid;
    if (pidFile >> pid && pid == getpid())
    {
        pidFile.close();
        unlink(options.pidFile().c_str());
    }

    throw 0;                    // ends the program or the child process
}







