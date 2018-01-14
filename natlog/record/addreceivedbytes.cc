#include "record.ih"

void Record::addReceivedBytes(size_t  receivedBytes)
{
    d_receivedBytes += receivedBytes;
    d_lastUsed = ::time(0);
}

