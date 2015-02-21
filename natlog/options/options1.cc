#include "options.ih"

// at this time we're not running as a daemon, and all messages are sent to
// cout

Options::Options()
:
    d_arg(ArgConfig::instance())
{
    openConfig();

    if (not d_arg.option(&d_conntrackCommand, "conntrack-command"))
        d_conntrackCommand = s_defaultConntrackCommand + setProtocol() +
                             s_defaultConntrackArgs;

    setSyslogParams();

    setBoolMembers();

    string value;
    if (not d_arg.option(&value, 't'))
        d_time = s_time.find("raw");
    else 
        setTime(value);

    if (d_arg.option(&value, "conntrack-restart"))
        d_conntrackRestart = stoul(value);
}
