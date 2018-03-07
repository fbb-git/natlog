#include "icmp.ih"

void ICMP::logConnection(Record const &record) const
{
    stdMsg() << "from " << record.beginTime() << 
                " thru " << record.endTime() << 
                ShowSeconds::utcMarker() << ": icmp " <<
                record.sourceIPstr() << 
                " (via: " << record.viaIPstr()  << ") "
                "to " << record.destIPstr() << "; "
                "sent: " << record.sentBytes() << ", "
                "received: " << record.receivedBytes() << 
                logType().first << endl;

    logCSV(record);
}
