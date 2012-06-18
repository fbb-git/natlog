#include "conntrack.ih"

Conntrack::Conntrack(ostream &syslog)
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_syslog(syslog)
{
    char const *conntrack = d_options.conntrackPath().c_str();

    if (access(conntrack, R_OK | X_OK) != 0)
    {
        d_syslog << "[Fatal] Can't execute " << conntrack << endl;
        fmsg << "Can't execute " << conntrack << endl;
    }
 
    imsg << "Calling `" << d_options.conntrackPath() + 
            " -p tcp -E -n -o timestamp -e NEW,DESTROY'\n";
}
