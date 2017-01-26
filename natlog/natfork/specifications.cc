#include "natfork.ih"

void NatFork::specifications()
{
    if (d_options.verbose() >= 2)
    {
        switch (d_mode)
        {
            case CONNTRACK:
                d_stdMsg << "conntrack command: " << 
                            d_options.conntrackCommand() << endl;
                d_stdMsg << "max # conntrack restarts: " << 
                            d_options.conntrackRestart() << endl;
                d_stdMsg << "protocol(s): " << d_options.protocols() << endl;
            break;

            case PCAP:
                d_stdMsg << "PCAP mode: " << 
                            d_options[0] << ' ' << d_options[1] << endl;
            break;

            case ERROR:
                d_stdMsg << "Mode specification error" << endl;
            break;
        }

        d_stdMsg << "config file: " << d_options.configPath() << endl;
        d_stdMsg << "daemon: " << boolalpha << d_options.daemon() << endl;
        d_stdMsg << "using syslog: " << d_options.syslog() << endl;
        d_stdMsg << "PID file: " << d_options.pidFile() << endl;
        d_stdMsg << "using stdout: " << d_options.stdout() << endl;
        d_stdMsg << "syslog facility: " << d_options.facility() << endl;
        d_stdMsg << "syslog priority: " << d_options.priority() << endl;
        d_stdMsg << "syslog tag: " << d_options.syslogTag() << endl;
        d_stdMsg << "time type `" << d_options.timeTxt() << '\'' << endl;
        d_stdMsg << "verbose: " << d_options.verbose() << endl;
        d_stdMsg << "warn: " << d_options.warnings() << endl;

        if (d_options.verbose() == 3)
        {
            d_stdMsg << "ENDS (> 2 times verbose)" << endl;
            throw 0;
        }
    }

    if (d_options.timeSpecError().length() == 0)
    {
        if (d_options.verbose() < 2)
            imsg << "Using time type `" << d_options.timeTxt() << '\'' << 
                                                                        endl;
    }
    else
        wmsg << "Time specifcation `" << d_options.timeSpecError() <<
                "' not supported. Using `" << d_options.timeTxt() << 
                "' instead" << endl;
}
