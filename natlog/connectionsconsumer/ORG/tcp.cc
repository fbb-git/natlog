#include "connectionsconsumer.ih"

//static size_t count = 0;

void ConnectionsConsumer::tcp(Record *record)
{
//cerr << "\n"
//        "---------------\n\n" <<
//        ++count << " #: " << d_tcp.size() << ": ";
//
//CERR << *record << '\n';

    lock_guard<mutex> lg(d_tcpMutex);

     switch (record->type())
     {
        case Record::IN:
            tcpInDev(record);
        break;

        case Record::OUT:
            tcpOutDev(record);
        return;

        case Record::NEW:
            d_tcp.insert( value_type{ record->srcKey(), record } );
        return;

        case Record::DESTROY:
            tcp_udpDestroy(d_tcp, record, "tcp");
        return;
    }
}

