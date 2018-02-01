#include "natfork.ih"

void NatFork::specifications()
{
    if (d_options.verbose() == 2)
    {
        switch (d_mode)
        {
            case Options::CONNTRACK:
                d_stdMsg << "CONNTRACK mode: command = `" << 
                            d_options.conntrackCommand() << '\'' << endl;
                d_stdMsg << "conntrack device: " << 
                            d_options.conntrackDevice() << endl;
                if (d_options.IPheaderSize() != 0)
                    d_stdMsg << "conntrack IP header size correction: " << 
                                d_options.IPheaderSize() << " bytes" << endl;
                else
                    d_stdMsg << "no conntrack IP header size correction" << 
                                                                        endl;
                d_stdMsg << "max # conntrack restarts: " << 
                            d_options.conntrackRestart() << endl;
            break;

            case Options::DEVICE:
                d_stdMsg << "DEVICE mode: " << 
                            d_options[0] << ' ' << d_options[1] << endl;
            break;

            case Options::TCPDUMP:
                d_stdMsg << "TCPDUMP mode: " << 
                    d_options[0] << ' ' << d_options[1] << 
                                                d_options[2] << ' ' << 
                    d_options[3] << ' ' << d_options[4] << ' ' << 
                                                d_options[5] << endl;
            break;
        }

        d_stdMsg << boolalpha;
        d_stdMsg << "config file: " << d_options.configPath() << endl;
        d_stdMsg << "log data: " << (d_options.logData().length() ? 
                                    d_options.logData() : ""s) << endl;
        d_stdMsg << "daemon: " << d_options.daemon() << endl;
        d_stdMsg << "PID file: " << d_options.pidFile() << endl;
        d_stdMsg << "protocol(s): " << d_options.protocolNames() << endl;
        d_stdMsg << "using syslog: " << d_options.syslog() << endl;
        d_stdMsg << "using stdout: " << d_options.stdout() << endl;
        d_stdMsg << "syslog facility: " << d_options.facility() << endl;
        d_stdMsg << "syslog priority: " << d_options.priority() << endl;
        d_stdMsg << "syslog tag: " << d_options.syslogTag() << endl;
        d_stdMsg << "time type `" << d_options.timeTxt() << '\'' << endl;
        d_stdMsg << "ttl (udp, icmp) " << d_options.ttl() << " seconds" << 
                                                                    endl;
        d_stdMsg << "verbose: " << d_options.verbose() << endl;
//        d_stdMsg << "warn: " << d_options.warnings() << endl;
        d_stdMsg << noboolalpha;
    }

    if (d_options.timeSpecError().length() != 0)
        d_stdMsg << "Time specifcation `" << d_options.timeSpecError() <<
                "' not supported. Using `" << d_options.timeTxt() << 
                "' instead" << endl;
    else if (d_options.verbose() < 2)
        imsg << "Using time type `" << d_options.timeTxt() << '\'' << endl;
}


