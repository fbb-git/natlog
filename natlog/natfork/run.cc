#include "natfork.ih"

void NatFork::run()
{
    switch (d_mode)
    {
        case Options::CONNTRACK:
            conntrackMode();
        break;

        case Options::DEVICE:
        break;

        case Options::TCPDUMP:
            if (d_options.daemon())
                d_stdMsg << 
                        "TCPDUMP processing cannot be used in daemon mode" <<
                        endl;
        break;
    }

    
    if (d_options.daemon())
        fork();
    else
        childProcess();
}


