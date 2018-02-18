#include "record.ih"

void Record::addSentBytes(Record const *next)
{
    d_sentBytes += next->payload();

    setEndTime(next);
}

