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

    string value;
    if (not d_arg.option(&value, 't'))
        d_time = RAW;
    else 
        setTime(value);

    if (emsg.count())           // encountered errors? Then quit.
        throw 1;

    d_delayMusecs = d_arg.option(&value, "delay-musecs") ?
                        A2x(value)
                    :
                        s_defaultDelayMusecs;
}




