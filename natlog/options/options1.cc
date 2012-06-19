#include "options.ih"

// at this time we're not running as a daemon, and all messages are sent to
// cout

Options::Options()
:
    d_arg(ArgConfig::instance())
{
    openConfig();

    if (not d_arg.option(&d_conntrackPath, "conntrack-path"))
        d_conntrackPath = s_defaultConntrackPath;

    setSyslogParams();

    setBoolMembers();

    string time;
    if (not d_arg.option(&time, 't'))
        d_time = RAW;
    else 
        setTime(time);

    if (emsg.count())           // encountered errors? Then quit.
        throw 1;
}




