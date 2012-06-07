#include "conntrack.ih"

Conntrack::Conntrack()
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_syslog(d_options.syslogTag().c_str(), d_options.syslogPriority(), 
             d_options.syslogFacility())
{
    ShowTime::setDisplay(d_options.time());

    if (d_options.verbose())
    {
        cout << "Calling `" << d_options.conntrackPath() + 
                " -p tcp -E -n -o timestamp -e NEW,DESTROY'\n";

        if (not d_options.syslog())
            cout << "No syslog messages\n";
        else
            cout <<
                "Writing syslog messages using id `" << 
                d_options.syslogTag() << "', "
                "facility: " << d_options.facility() << ", "
                "priority: " << d_options.priority() << '\n';
    }
}

