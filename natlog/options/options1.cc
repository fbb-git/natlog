#include "options.ih"

// at this time we're not running as a daemon, and all messages are sent to
// cout

Options::Options()
:
    d_arg(ArgConfig::instance())
{
    d_terminate = d_arg.option(0, "terminate");

    openConfig();

    if (d_terminate)
        return;

    setMode();

    setProtocol();

    if (d_mode == CONNTRACK)
        setConntrack();

    setSyslogParams();

    d_verbose = d_arg.option('V');      // not a bool, but a size_t
    if (d_verbose > 2)
        d_verbose = 2;                  // restrict the max. verbosity

    setBoolMembers();

    setTimeSpec();

    ArgConfig::instance().option(&d_logData, "log-data");
}

