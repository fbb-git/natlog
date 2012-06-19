#include "natfork.ih"

void NatFork::run()
{
    configureMsb();

    if (string(d_options[0]) == "conntrack")
        conntrackMode();
    else if (d_options.nArgs() == 2)
        d_mode = PCAP;
    else
    {
        usage(d_options.basename());
        throw 1;
    }

    if (d_options.daemon())
        fork();
    else
        childProcess();
}



