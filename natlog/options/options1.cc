#include "options.ih"

// at this time we're not running as a daemon, and all messages are sent to
// cout

Options::Options()
:
    d_arg(ArgConfig::instance())
{
    openConfig();

    setMode();
    setProtocol();

    if (d_mode == CONNTRACK)
        setConntrack();

    setSyslogParams();

    d_verbose = d_arg.option('V');      // not a bool, but a size_t

    setBoolMembers();
    setTimeSpec();
}
