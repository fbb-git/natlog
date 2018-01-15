#include "connectionsconsumer.ih"

void ConnectionsConsumer::udp(Record &record)
{
    lock_guard<mutex> lg(d_udpMutex);

     switch (record.type())
    {
        case Record::IN:
            udpIn(record);
        break;

        case Record::OUT:
            udpOut(record);
        return;

        case Record::NEW:
            d_udp.insert( value_type{ record.key(), record } );
        return;

        case Record::DESTROY:
            udpDestroy(record);
        return;
    }
}









