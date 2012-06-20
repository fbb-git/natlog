#include "natfork.ih"

NatFork::NatFork()
:
    d_options(Options::instance()),
    d_out(&d_msb)
{
    if (d_options.syslog())
    {
        d_syslog.reset(
            new SyslogStream(
                d_options.syslogTag().c_str(), d_options.syslogPriority(), 
                d_options.syslogFacility()
            )
        );
        d_msb.insert(*d_syslog);
    }

    if (d_options.stdout())
        d_msb.insert(cout);

    if (d_options.daemon())
    {
        if (d_options.verbose() && d_options.syslog())
            imsg.reset(*d_syslog);
        else
            imsg.off();
    }
    else if (not d_options.verbose())
        imsg.off();
}



