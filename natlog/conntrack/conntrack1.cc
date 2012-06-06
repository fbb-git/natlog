#include "conntrack.ih"

Conntrack::Conntrack()
:
    d_options(Options::instance()),
    d_conntrack(Process::COUT, d_options.conntrackPath() + 
                                " -p tcp -E -n -o timestamp -e NEW,DESTROY"),
    d_syslog(d_options.syslogIdent().c_str(), d_options.syslogPriority(), 
             d_options.syslogFacility())
{
    if (d_options.verbose())
    {
        imsg << "Calling `" << d_options.conntrackPath() + 
                " -p tcp -E -n -o timestamp -e NEW,DESTROY'" << endl;

        if (not d_options.syslog())
        {
            imsg << "No syslog messages" << endl;
            d_syslog.setstate(ios::failbit);
        }
        else
            imsg <<
                "Writing syslog messages using id `" << 
                d_options.syslogIdent() << "', "
                "facility: " << d_options.facility() << ", "
                "priority: " << d_options.priority() << endl;
    }
}
