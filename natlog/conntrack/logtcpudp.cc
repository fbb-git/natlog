#include "conntrack.ih"

void Conntrack::logTcpudp(ConntrackRecord::Record const &record, 
                        string const &endSeconds, 
                        string endMicroSecs)
{
    endMicroSecs.insert(0, 6 - endMicroSecs.length(), '0');

    d_stdMsg << "from " << 
                ShowSeconds(record.seconds) << ':' << record.musecs << 
            " until " << 
                ShowSeconds(endSeconds) << ':' << endMicroSecs << 
                                        ShowSeconds::utcMarker() << ": " <<
            record.protocol << ' ' <<
            record.sourceIP << ':' << record.sourcePort << 
               " (via: " << record.viaIP << ':' << record.viaPort << ") "
        "to " << record.destIP << ':' << record.destPort << ". "
        "Sent: " << record.outBytes << ", "
        "received: " << record.inBytes << endl;
}
