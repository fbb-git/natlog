#include "conntrack.ih"

Conntrack::Conntrack(ostream &stdMsg)
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT | Process::CERR, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_stdMsg(stdMsg)
{
    if (access("/proc/net/ip_conntrack", R_OK) != 0)
        throw Errno(1, "[Fatal] ") << "Cannot read /proc/net/ip_conntrack";

    imsg << "Calling `" << d_options.conntrackPath() + 
            " -p tcp -E -n -o timestamp -e NEW,DESTROY'" << endl;
}
