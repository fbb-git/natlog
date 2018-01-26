#include "connectionsconsumer.ih"

void ConnectionsConsumer::logICMP(Record const &record,
                                  [[maybe_unused]] char const *)
{
    d_stdMsg << "from " << record.beginTime() << 
                " until " << record.endTime() << 
                ShowSeconds::utcMarker() << ": icmp " <<
                record.sourceIPstr() << 
                " (via: " << record.viaIPstr()  << ") "
                "to " << record.destIPstr() << "; "
                "sent: " << record.sentBytes() << ", "
                "received: " << record.receivedBytes() << 
                (record.hasEndTime() ? "" : " (INCOMPLETE)") << endl;

    (this->*d_logData)(record, "icmp");
}
