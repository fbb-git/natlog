#include "record.ih"

void Record::addSentBytes(size_t  sentBytes)
{
    d_sentBytes += sentBytes;
    d_lastUsed = ::time(0);
}

