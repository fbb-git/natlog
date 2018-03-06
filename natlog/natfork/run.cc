#include "natfork.ih"

//f: NatFork::run()
    //c: NatFork::childProcess()
    //c: NatFork::parentProcess()

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


