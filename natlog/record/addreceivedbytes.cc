#include "record.ih"

void Record::addReceivedBytes(Record const *next)
{
    d_receivedBytes += next->payload();
    
    setEndTime(next);
}

