#include "connectionsconsumer.ih"

void ConnectionsConsumer::synRecord(Record *record)
{
    if (                                            // package not sent
        not g_nic.mask(Record::IN, record->sourceIP())
        ||
        g_nic.mask(Record::IN, record->destIP())    // or local connection
    )
        delete record;                              // then ignore
    else                                            // else insert
        d_tcp.insert( value_type{ record->sequenceKey(), record } );
            // insertion also means: the record pointer is transferred
            // to the tcp-map.
}
