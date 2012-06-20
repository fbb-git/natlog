#include "natfork.ih"

void NatFork::childProcess()
{
    ShowSeconds::setFormat();

    if (d_options.daemon())
        prepareDaemon();

    OFdStream out(d_pipe.writeFd());        // the message to the parent
                                            // (if any)

    if (not d_options.warnings())
        wmsg.off();

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
        out << err.why() << endl;           // If the daemon can't start,
                                            // write a message.

        // the failure message must be sent within Options::delaySe0.5 seconds. I cannot
        // otherwise determine whether conntrack runs. If it runs it writes a
        // message to the std error stream, but that's only known once
        // Conntrack run's getline fails. But if it doesn't fail, there's no
        // telling how much time it takes before getline returns, and I don't
        // want the parent to have to wait that long. Therefore, if no message
        // has been received within 0.5 seconds then the child apparently is
        // OK 
    }

        // when the child process ends it throws away its own pid file:
    ifstream pidFile(d_options.pidFile());
    pid_t pid;
    if (pidFile >> pid && pid == getpid())
    {
        pidFile.close();
        unlink(d_options.pidFile().c_str());
    }

    throw 0;                    // ends the program or the child process
}







