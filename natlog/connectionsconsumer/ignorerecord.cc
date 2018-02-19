#include "connectionsconsumer.ih"

void ConnectionsConsumer::ignoreRecord(Record *next)
{
//CERR << '\n';
    delete next;
}
