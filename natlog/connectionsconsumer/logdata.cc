#include "connectionsconsumer.ih"

void ConnectionsConsumer::logData(Record const &record, char const *type)
{
    static size_t nr = 0;

    d_logDataStream << 
                        record.protocolStr()    << ',' <<

            setw(11) << ntohl(record.sourceIP())<< ',' <<
            setw(16) << record.sourceIPstr()    << ',' <<
            setw(8)  << record.sourcePort()     << ',' <<

            setw(11) << ntohl(record.destIP())  << ',' <<
            setw(16) << record.destIPstr()      << ',' <<
            setw(8)  << record.destPort()       << ',' <<

            setw(11) << record.sentBytes()      << ',' <<
            setw(11) << record.receivedBytes()  << ',' <<

            setw(11) << record.inSeconds()      << ',' <<
            setw(11) << record.seconds()        << ", " <<
                         record.beginTime()     << ", " <<
                         record.endTime()       << ", " <<
            setw(7)  << d_complete              << '\n';

    if (++nr % d_options.logDataFlush() == 0)
        d_logDataStream.flush();        
}






