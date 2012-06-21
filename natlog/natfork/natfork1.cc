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
}
