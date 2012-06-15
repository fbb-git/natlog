#include "conntrack.ih"

void Conntrack::log(ConntrackRecord::Record const &record, 
                        string const &endSeconds, 
                        string endMicroSecs)
{
    endMicroSecs.insert(0, 6 - endMicroSecs.length(), '0');

    ostringstream out1;
    out1 << "from " << 
                ShowSeconds(record.seconds) << ':' << record.musecs << 
            " until " << 
                ShowSeconds(endSeconds) << ':' << endMicroSecs << 
                                        ShowSeconds::utcMarker() << ':';

    ostringstream out2;
    out2 << ' ' << record.sourceIP << ':' << record.sourcePort << 
               " (via: " << record.viaIP << ':' << record.viaPort << ") "
        "to " << record.destIP << ':' << record.destPort;

    if (d_options.stdout())
        cout << out1.str() << "\n"
                "   " << out2.str() << endl;

    d_syslog << out1.str() << out2.str() << endl;
}
