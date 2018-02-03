#include "options.ih"

void Options::setLogParams()
{
    string value;

    if (not d_arg.option(&d_log, "log"))     
    {
        d_log = "syslog";
        if (not d_arg.option(&d_syslogTag, "syslog-tag"))
            d_syslogTag = s_defaultSyslogIdent;
    
        setSyslogFacility();
        setSyslogPriority();
    }
    else if (d_log == "off")                    // no logging
        d_log.clear();

    if (d_arg.option(&d_logData, "log-data"))
    {
        if (d_arg.option(&value, "log-data-flush"))
            d_logDataFlush = max(1LU, stoul(value));
    }

    if (d_arg.option(&value, "log-rotate"))     // log file rotation in days
        d_logRotate = stoul(value);             
}
