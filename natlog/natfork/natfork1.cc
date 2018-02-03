#include "natfork.ih"

NatFork::NatFork()
:
    d_options(Options::instance()),
    d_log(d_options.logRotate()),
    d_stdMsg(&d_multiStreambuf),
    d_mode(d_options.mode())
{
    setupStdMsg();

    if (not d_options.daemon())
        setupNonDaemonMsg();

    else 
    {
        if (not (d_options.mode() == Options::TCPDUMP))
            setupDaemonMsg();
        else
        {
            d_options.foreground();
            setupNonDaemonMsg();
            d_stdMsg << "mode TCPDUMP: ignoring daemon mode" << endl;
        }
    }

    specifications();
}
