#include "natfork.ih"

void NatFork::childProcess()
{
    Options &options(Options::instance());

    ShowSeconds::setFormat(options.time());

    Syslogger syslog(options);

    if (string(options[0]) == "conntrack")
    {
        Conntrack conntrack(syslog);
        conntrack.run();
    }
    else if (options.nArgs() == 2)
    {
        Devices devices(syslog);
        devices.run();
    }
    else
    {
        usage(options.basename());
        throw 1;
    }

    throw 0;                    // ends the program or the child process
}
