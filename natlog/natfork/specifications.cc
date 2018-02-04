#include "natfork.ih"

#include <iomanip>

void NatFork::specifications()
{
    if (d_options.verbose() >= 2)
    {
        d_stdMsg << left;

        switch (d_mode)
        {
            case Options::CONNTRACK:
                d_stdMsg << "CONNTRACK mode" << endl;
                d_stdMsg << setw(25) << setw(25) << "command: `" << 
                            d_options.conntrackCommand() << '\'' << endl;
                d_stdMsg << setw(25) << "conntrack device: " << 
                            d_options.conntrackDevice() << endl;
                if (d_options.IPheaderSize() != 0)
                    d_stdMsg << setw(25) << 
                                "conntrack IP header size correction: " << 
                                d_options.IPheaderSize() << " bytes" << endl;
                else
                    d_stdMsg << setw(25) << 
                                "no conntrack IP header size correction" << 
                                                                        endl;
                d_stdMsg << setw(25) << "max # conntrack restarts: " << 
                                d_options.conntrackRestart() << endl;
            break;

            case Options::DEVICE:
                d_stdMsg << "DEVICE mode" << endl;
                d_stdMsg << setw(25) << "devices: " <<
                                d_options[0] << ' ' << d_options[1] << endl; 
            break;

            case Options::TCPDUMP:
                d_stdMsg << "TCPDUMP mode" << endl;
                d_stdMsg << setw(25) << "specifications: "  << 
                                d_options[0] << ' ' << 
                                d_options[1] << ' ' << d_options[2] << ' ' << 
                                d_options[3] << ' ' << 
                                d_options[4] << ' ' << d_options[5] << endl;
            break;
        }

        d_stdMsg << setw(25) << boolalpha;
        d_stdMsg << setw(25) << "config file: " << 
                                            d_options.configPath() << endl;

        if (string const &logData = d_options.logData(); not logData.empty())
            d_stdMsg << setw(25) << "log data: " << logData << endl;

        if (d_options.rotateFreq() != 0 and d_options.nRotations() != 0)
        {
            d_stdMsg << setw(25) << "rotating log files: " << "each " << 
                        d_options.rotateFreq() << 
                                        d_options.rotateTimeSpec() << endl;
            d_stdMsg << setw(25) << "number of rotated files: " << 
                                        d_options.nRotations() << endl;
        }

        d_stdMsg << setw(25) << "daemon: " << d_options.daemon() << endl;

        if (d_options.daemon())
            d_stdMsg << setw(25) << "PID file: " << 
                                            d_options.pidFile() << endl;

        d_stdMsg << setw(25) << "protocol(s): " << 
                                            d_options.protocolNames() << endl;

        if (not d_options.log().empty())
        {
            d_stdMsg << setw(25) << "using log: " << d_options.log() << endl;

            if (d_options.log() == "syslog")
            {
                d_stdMsg << setw(25) << "   facility: " << 
                                                d_options.facility() << endl;
                d_stdMsg << setw(25) << "   priority: " << 
                                                d_options.priority() << endl;
                d_stdMsg << setw(25) << "   tag: " << 
                                                d_options.syslogTag() << endl;
            }
        }

        d_stdMsg << setw(25) << "using stdout: " << 
                                                d_options.stdout() << endl;

        d_stdMsg << setw(25) << "time type: " << d_options.timeTxt() << endl;

        if (d_mode != Options::CONNTRACK)
        {
            d_stdMsg << setw(25) << "ttl (udp, icmp): " << d_options.ttl() << 
                                                        " seconds" << endl;
            d_stdMsg << setw(25) << "ttl (tcp): " << d_options.ttlTCP() << 
                                                        " seconds" << endl;
        }

        d_stdMsg << setw(25) << "verbosity: " << d_options.verbose() << endl;
        d_stdMsg << setw(25) << noboolalpha;
    }

    if (d_options.timeSpecError().length() != 0)
        d_stdMsg << setw(25) << "Time specifcation `" << 
                d_options.timeSpecError() << "' not supported. Using `" << 
                d_options.timeTxt() << "' instead" << endl;
    else if (d_options.verbose() < 2)
        imsg << "Using time type `" << d_options.timeTxt() << '\'' << endl;

    if (d_options.verbose() == 2)
        throw 0;
}



