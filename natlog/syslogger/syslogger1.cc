#include "syslogger.ih"

Syslogger::Syslogger(Options &options)
:
    SyslogStream(options.syslogTag().c_str(), options.syslogPriority(), 
                 options.syslogFacility())
{
    if (not options.syslog())
        setstate(ios::failbit);
}
