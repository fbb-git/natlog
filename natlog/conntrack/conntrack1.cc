#include "conntrack.ih"

Conntrack::Conntrack(ostream &stdMsg)
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT | Process::CERR, d_options.conntrackCommand()),
    d_stdMsg(stdMsg)
{
    if (access("/proc/net/ip_conntrack", R_OK) != 0)
        throw Exception() << "Cannot read /proc/net/ip_conntrack";

    imsg << "Calling `" << d_options.conntrackCommand() << endl;
}
