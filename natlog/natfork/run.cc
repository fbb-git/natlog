#include "natfork.ih"

void NatFork::run()
{
    if (string(d_options[0]) == "conntrack")
        conntrackMode();
    else if (d_options.nArgs() == 2)
        d_mode = PCAP;
    else
    {
        d_stdMsg << "[Fatal] invalid argument(s): `";
        for (size_t idx = 0, end = d_options.nArgs(); idx != end; ++idx)
            d_stdMsg << d_options[idx] << (idx + 1 == end ? '\'' : ' ');
        d_stdMsg << endl;

        throw Options::FAILED;
    }

    
    if (d_options.daemon())
        fork();
    else
        childProcess();
}








