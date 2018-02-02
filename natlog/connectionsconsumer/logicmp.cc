#include "connectionsconsumer.ih"

void ConnectionsConsumer::logICMP(Record const &record,
                                  [[maybe_unused]] char const *)
{
    d_stdMsg << "from " << record.beginTime() << 
                " thru " << record.endTime() << 
                ShowSeconds::utcMarker() << ": icmp " <<
                record.sourceIPstr() << 
                " (via: " << record.viaIPstr()  << ") "
                "to " << record.destIPstr() << "; "
                "sent: " << record.sentBytes() << ", "
                "received: " << record.receivedBytes() << 
                (d_complete ? "" : " (INCOMPLETE)") << endl;

    (this->*d_logData)(record, "icmp");
}
