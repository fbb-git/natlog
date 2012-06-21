#include "conntrack.ih"

void Conntrack::log(ConntrackRecord::Record const &record, 
                        string const &endSeconds, 
                        string endMicroSecs)
{
    endMicroSecs.insert(0, 6 - endMicroSecs.length(), '0');

    d_stdMsg << "from " << 
                ShowSeconds(record.seconds) << ':' << record.musecs << 
            " until " << 
                ShowSeconds(endSeconds) << ':' << endMicroSecs << 
                                        ShowSeconds::utcMarker() << ": " <<
            record.sourceIP << ':' << record.sourcePort << 
               " (via: " << record.viaIP << ':' << record.viaPort << ") "
        "to " << record.destIP << ':' << record.destPort << endl;
}
