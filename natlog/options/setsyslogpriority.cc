#include "options.ih"

void Options::setSyslogPriority()
{
    string option;
    if (not d_arg.option(&option, "syslog-priority"))
        d_syslogPriority = s_syslogPriorities.find(s_defaultSyslogPriority);
    else
    {
        d_syslogPriority = s_syslogPriorities.find(option);
        if (d_syslogPriority == s_syslogPriorities.end())
            emsg << "Syslog priority `" << option << "' not supported. "
                    "(see the man-page)" << endl;
    }            
}
