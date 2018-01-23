#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmp(Record &record)
{
    lock_guard<mutex> lg(d_icmpMutex);

    auto iter = d_icmp.find(record.key());  // key is the record's ID

    if (iter == d_icmp.end())               // not found: store data as
    {
        switch (record.type())
        {
            case Record::IN:
                record.addSentBytes(record.payload());  // initial payload
            [[fallthrough]]

            case Record::NEW:
                d_icmp.insert( value_type{ record.key(), record } );
            [[fallthrough]]

            case Record::OUT:               // ongoing icmp record: ours
            return;                         // must be NEW or IN

            case Record::DESTROY:
            break;
        }
    }

    switch (record.type())
    {
        case Record::IN:
            if (iter->second.sourceIP() == record.sourceIP())
                iter->second.addSentBytes(record.payload());
            else
                iter->second.addReceivedBytes(record.payload());

            iter->second.setEndTime(record);
        return;

        case Record::OUT:
            if (iter->second.destIP() == record.destIP())
                iter->second.setViaIP(record.sourceIP());
        return;

        case Record::NEW:
            d_icmp.insert( value_type{ record.key(), record } );

        case Record::DESTROY:
             icmpDestroy(record);
        return;
    }
}












