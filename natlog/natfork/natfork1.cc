#include "natfork.ih"

NatFork::NatFork()
:
    d_options(Options::instance()),
    d_stdMsg(&d_multiStreambuf)
{
    setupStdMsg();

    if (d_options.daemon())
        setupDaemonMsg();
    else
        setupNonDaemonMsg();

    d_mode = string(d_options[0]) == "conntrack" ? CONNTRACK :
             d_options.nArgs() == 2              ? PCAP      :
                                                   ERROR;

    specifications();
}
