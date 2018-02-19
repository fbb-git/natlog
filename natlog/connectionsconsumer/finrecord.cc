#include "connectionsconsumer.ih"

void ConnectionsConsumer::finRecord(Record *record)
{
//CERR << '\n';
    auto iter = d_tcp.find(record->srcKey());

    if (iter == d_tcp.end())                    // the local host doesn't FIN
        iter = d_tcp.find(record->dstKey());    // maybe it's the remote host

    if (iter != d_tcp.end())
    {
        logTCP_UDP(iter->second, "tcp");    
        erase(d_tcp, iter);                 // remove the entry
    }
//else
//CERR << "FIN: NO KEY " << record->srcKey() << '\n';

    delete record;
}
