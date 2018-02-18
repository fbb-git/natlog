#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmp(Record *record)
{
    lock_guard<mutex> lg(d_icmpMutex);

    switch (record->type())
    {
        case Record::IN:
            icmpIn(record);
        return;

        case Record::OUT:
            icmpOut(record);
        return;

        case Record::NEW:
            d_icmp.insert( value_type{ record->key(), record } );
        return;

        case Record::DESTROY:
            icmpDestroy(record);
        return;
    }
}
