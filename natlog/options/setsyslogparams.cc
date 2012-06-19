#include "options.ih"

void Options::openSyslog()
{
    d_useSyslog = not d_arg.option(0, "no-syslog");

    if (d_useSyslog)
    {
        if (not d_arg.option(&d_syslogTag, "syslog-tag"))
            d_syslogTag = s_defaultSyslogIdent;
    
        setSyslogFacility();
        setSyslogPriority();
    
        if (emsg.count())           // encountered errors? Then quit.
            throw 1;
    }
}
