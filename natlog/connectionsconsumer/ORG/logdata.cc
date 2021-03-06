#include "connectionsconsumer.ih"

void ConnectionsConsumer::logData(Record const *record, char const *type)
{
    auto ptr = ShowSeconds::utcFormat();

    d_logDataStream << 
                        record->protocolStr()    << ',' <<

            setw(11) << ntohl(record->sourceIP())<< ',' <<
            setw(16) << record->sourceIPstr()    << ',' <<
            setw(8)  << record->sourcePort()     << ',' <<

            setw(11) << ntohl(record->destIP())  << ',' <<
            setw(16) << record->destIPstr()      << ',' <<
            setw(8)  << record->destPort()       << ',' <<

            setw(11) << record->sentBytes()      << ',' <<
            setw(11) << record->receivedBytes()  << ',' <<

            setw(11) << record->inSeconds()      << ',' <<
            setw(11) << record->seconds()        << ", " <<
                         record->beginTime()     << ", " <<
                         record->endTime()       << ", " <<

            setw(10) << s_logType[d_logType].second << endl;

        ShowSeconds::setFormat(ptr);
}






