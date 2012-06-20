#include "natfork.ih"

void NatFork::run()
{
    if (string(d_options[0]) == "conntrack")
        conntrackMode();
    else if (d_options.nArgs() == 2)
        d_mode = PCAP;
    else
    {
        imsg << "invalid argument(s) specified. First was: `" << 
                d_options[0] << '\'' << endl;
        throw 1;
    }

    if (d_options.daemon())
        fork();
    else
        childProcess();
}



