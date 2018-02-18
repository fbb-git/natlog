#include "connectionsconsumer.ih"

void ConnectionsConsumer::ignoreRecord(Record *next)
{
    delete next;
}
