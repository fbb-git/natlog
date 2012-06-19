#include "natfork.ih"

void NatFork::run()
{
    Options &options = Options::instance();

    Syslogger syslog(options);

    if (options.syslog())
        d_msb.insert(syslog);
    if (options.stdout())
        d_msb.insert(cout);

    if (string(options[0]) == "conntrack")
    {
        char const *conntrack = options.conntrackPath().c_str();

        if (access(conntrack, R_OK | X_OK) != 0)
        {
            d_out << "[Fatal] Can't execute " << conntrack << endl;
            throw 1;
        }
        d_mode = CONNTRACK;
    }
    else if (options.nArgs() == 2)
        d_mode = PCAP;
    else
    {
        usage(options.basename());
        throw 1;
    }

    if (Options::instance().daemon())
        fork();
    else
        childProcess();
}



