#include "conntrack.ih"

Conntrack::Conntrack(ostream &syslog)
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_syslog(syslog)
{
    imsg << "Calling `" << d_options.conntrackPath() + 
            " -p tcp -E -n -o timestamp -e NEW,DESTROY'\n";
}
