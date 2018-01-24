#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcp(Record &record)
{
    lock_guard<mutex> lg(d_tcpMutex);

     switch (record.type())
    {
        case Record::IN:
            tcpIn(record);
        break;

        case Record::OUT:
            tcpOut(record);
        return;

        case Record::NEW:
            d_tcp.insert( value_type{ record.key(), record } );
        return;

        case Record::DESTROY:
            tcp_udpDestroy(d_tcp, record, "tcp");
        return;
    }
}

