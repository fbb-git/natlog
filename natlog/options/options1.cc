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

    setBoolMembers();

    setTimeSpec();

    if (d_arg.option(&d_logData, "log-data"))
    {
        string value;
        if (d_arg.option(&value, "log-data-flush"))
            d_logDataFlush = max(1LU, stoul(value));
    }   
}

