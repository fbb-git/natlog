#include "natfork.ih"

void NatFork::run()
{
    switch (d_mode)
    {
        case CONNTRACK:
            conntrackMode();
        // FALLING THROUGH
        case PCAP:
        break;

        case ERROR:
        {
            d_stdMsg << "[Fatal] invalid argument(s): `";
            for (size_t idx = 0, end = d_options.nArgs(); idx != end; ++idx)
                d_stdMsg << d_options[idx] << (idx + 1 == end ? '\'' : ' ');
            d_stdMsg << endl;
        }    
        throw Options::FAILED;
    }

    
    if (d_options.daemon())
        fork();
    else
        childProcess();
}








