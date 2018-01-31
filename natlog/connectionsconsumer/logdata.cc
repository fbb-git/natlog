#include "connectionsconsumer.ih"

void ConnectionsConsumer::logData(Record const &record, char const *type)
{
    static size_t nr = 0;

    d_logDataStream << 
                        record.protocolStr()    << ',' <<

            setw(11) << record.sourceIP()       << ',' <<
            setw(16) << record.sourceIPstr()    << ',' <<
            setw(8)  << record.sourcePort()     << ',' <<

            setw(11) << record.destIP()         << ',' <<
            setw(16) << record.destIPstr()      << ',' <<
            setw(8)  << record.destPort()       << ',' <<

            setw(10) << record.sentBytes()      << ',' <<
            setw(10) << record.receivedBytes()  << ',' <<

            setw(11) << record.inSeconds()      << ',' <<
            setw(11) << record.seconds()        << ", " <<
                         record.beginTime()     << ", " <<
                         record.endTime()       << '\n';

    if (++nr % 32 == 0)
        d_logDataStream.flush();        
}






