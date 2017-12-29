#include "conntrack.ih"

Conntrack::Conntrack(ostream &stdMsg)
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_accept(d_options.protocols())
{
    if (access(d_options.conntrackDevice(), R_OK) != 0)
        throw Exception() << "Cannot read " << d_options.conntrackDevice();

    Signal::instance().add(SIGHUP, *this);      // ignored
    Signal::instance().add(SIGTERM, *this);
}
