#include "connectionsconsumer.ih"

//static size_t count = 0;

void ConnectionsConsumer::icmp(Record *record)
{
//cerr << "\n"
//        "---------------\n\n" <<
//        ++count << ": ";
//
//CERR << *record << '\n';

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
