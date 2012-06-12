#include "natfork.ih"

void NatFork::childProcess()
{
    Options &options(Options::instance());

    SyslogStream syslog(options.syslogTag().c_str(), options.syslogPriority(), 
                        options.syslogFacility());

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
