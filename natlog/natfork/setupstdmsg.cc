#include "natfork.ih"

void NatFork::setupStdMsg()
{
    if (d_options.stdout())             // if --stdout, then messages also go
        d_multiStreambuf.insert(cout);  // to stdout

    if (d_options.log().empty())        // no messages
        return;
        
    if (d_options.log() == "syslog")
    {
        d_syslog.reset(
            new SyslogStream(
                d_options.syslogTag().c_str(), d_options.syslogPriority(), 
                d_options.syslogFacility()
            )
        );

        d_multiStreambuf.insert(*d_syslog);

        checkSyslogParam("facility", d_options.facility(), 
                                     d_options.syslogFacilityError());

        checkSyslogParam("priority", d_options.priority(), 
                                     d_options.syslogPriorityError());
        return;
    }

    // a log-file path was specified: create rotating stream 
    d_log.open(d_options.log());
    d_multiStreambuf.insert(d_log);
}





