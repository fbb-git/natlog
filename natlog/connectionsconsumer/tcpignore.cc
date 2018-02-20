#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcpIgnore(Record *next)
{
//CERR << '\n';
    delete next;
}
