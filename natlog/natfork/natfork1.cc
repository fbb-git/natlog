#include "natfork.ih"

NatFork::NatFork()
:
    d_options(Options::instance()),
    d_stdMsg(&d_multiStreambuf),
    d_mode(d_options.mode())
{
    setupStdMsg();

    if (d_options.debug())
        g_debug.rdbuf(d_stdMsg.rdbuf());

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




