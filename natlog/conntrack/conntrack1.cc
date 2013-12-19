#include "conntrack.ih"

Conntrack::Conntrack(ostream &stdMsg, ostream &parent)
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_parent(parent)
{
    if (access("/proc/net/ip_conntrack", R_OK) != 0)
        throw Exception() << "Cannot read /proc/net/ip_conntrack";

    imsg << "Calling `" << d_options.conntrackCommand() << endl;
}
