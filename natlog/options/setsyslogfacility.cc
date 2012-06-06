#include "options.ih"

void Options::setSyslogFacility()
{
    string option;
    if (not d_arg.option(&option, "syslog-facility"))
        d_syslogFacility = s_syslogFacilities.find(s_defaultSyslogFacility);
    else
    {
        d_syslogFacility = s_syslogFacilities.find(option);
        if (d_syslogFacility == s_syslogFacilities.end())
            emsg << "Syslog facility `" << option << "' not supported. "
                    "(see the man-page)" << endl;
    }            
}
