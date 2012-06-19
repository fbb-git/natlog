#include "options.ih"

Options::Options()
:
    d_arg(ArgConfig::instance())
{
    openConfig();

    if (not d_arg.option(&d_conntrackPath, "conntrack-path"))
        d_conntrackPath = s_defaultConntrackPath;

    openSyslog();

    setBoolMembers();

    string time;
    if (not d_arg.option(&time, 't'))
        d_time = RAW;
    else 
        setTime(time);

}




