#include "connectionsconsumer.ih"

void ConnectionsConsumer::logTCP_UDP(Record const &record, char const *type)
{
    if (record.viaIP() != 0)
    {
        d_stdMsg << "from " << record.beginTime() << 
            " thru " << record.endTime() << 
            ShowSeconds::utcMarker() << ":  " << type << ' ' <<
            record.sourceIPstr() << ':' << record.sourcePort() << 
            " (via: " << record.viaIPstr()  << ':' << record.viaPort() << ") "
            "to " << record.destIPstr() << ':' << record.destPort() << "; "
            "sent: " << record.sentBytes() << ", "
            "received: " << record.receivedBytes() << 
            (d_complete ? "" : " (INCOMPLETE)") << endl;

        (this->*d_logData)(record, "icmp");
    }
}

