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

    if (d_options.timeSpecError().length() == 0)
        imsg << "Using time type `" << d_options.timeTxt() << '\'' << endl;
    else
        wmsg << "Time specifcation `" << d_options.timeSpecError() <<
                "' not supported. Using `" << d_options.timeTxt() << 
                "' instead" << endl;
}
