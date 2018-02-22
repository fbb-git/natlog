#include "natfork.ih"

void NatFork::run()
{
    switch (d_mode)
    {
        case Options::CONNTRACK:
            conntrackMode();
        break;

        case Options::DEVICE:
        case Options::TCPDUMP:
        break;
    }
    
    if (d_options.daemon())
        fork();
    else
        childProcess();
}


