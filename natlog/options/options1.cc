#include "options.ih"

// at this time we're not running as a daemon, and all messages are sent to
// cout

Options::Options()
:
    d_arg(ArgConfig::instance())
{
    openConfig();

    if (d_arg.option(0, "conntrack-path"))
        throw Exception() << "Option 'conntrack-path' discontinued. "
                    "Use 'conntrack-command' instead";

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
}





