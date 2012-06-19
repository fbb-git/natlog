#include "conntrack.ih"

Conntrack::Conntrack(ostream &out)
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT | Process::CERR, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_out(out)
{
    imsg << "Calling `" << d_options.conntrackPath() + 
            " -p tcp -E -n -o timestamp -e NEW,DESTROY'" << endl;
}
