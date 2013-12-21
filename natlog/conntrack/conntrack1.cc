#include "conntrack.ih"

Conntrack::Conntrack(ostream &stdMsg)
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg)
{
    if (access("/proc/net/ip_conntrack", R_OK) != 0)
        throw Exception() << "Cannot read /proc/net/ip_conntrack";

    Signal::instance().add(SIGHUP, *this);      // ignored
    Signal::instance().add(SIGTERM, *this);
}
