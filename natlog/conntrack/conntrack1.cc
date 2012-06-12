#include "conntrack.ih"

Conntrack::Conntrack(SyslogStream &syslog)
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_syslog(syslog)
{
    ShowTime::setDisplay(d_options.time());

    if (d_options.verbose())
    {
        cout << "Calling `" << d_options.conntrackPath() + 
                " -p tcp -E -n -o timestamp -e NEW,DESTROY'\n";
    }

    if (d_options.time() == Options::UTC)
        d_utcMarker = " (UTC)";

    s_conntrack = &d_conntrack;
}
