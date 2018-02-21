#include "ipbase.ih"

    // logs TCP and UDP records
void IPbase::logConnection(Record const *record) const
{
    if (record->viaIP() != 0)
    {
          d_stdMsg << "from " << record->beginTime() << 
            " thru " << record->endTime() << 
            ShowSeconds::utcMarker() << ": " << 
            record->protocolStr() << ' ' <<
            record->sourceIPstr() << ',' << record->sourcePort() << 
            " (via: " << record->viaIPstr()  << ',' << 
                                                    record->viaPort() << ") "
            "to " << record->destIPstr() << ',' << record->destPort() << "; "
            "sent: " << record->sentBytes() << ", "
            "received: " << record->receivedBytes() << 
            s_logTypeText[s_logType].first << endl;

        logCSV(record);
    }
}

