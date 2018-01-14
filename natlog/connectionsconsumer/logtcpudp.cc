#include "connectionsconsumer.ih"

void ConnectionsConsumer::logTCP_UDP(Record const &record, char const *type)
{
    d_stdMsg << "from " << record.beginTime() << 
            " until " << record.endTime() << ":  " << type << ' ' <<
            record.sourceIPstr() << ':' << record.sourcePort() << 
            " (via: " << record.viaIPstr()  << ':' << record.viaPort() << ") "
            "to " << record.destIPstr() << ':' << record.destPort() << "; "
            "Sent: " << record.sentBytes() << ", "
            "received: " << record.receivedBytes() << 
            (record.hasEndTime() ? "" : " (INCOMPLETE)") << endl;
}

