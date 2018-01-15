#include "record.ih"

void Record::reverse()
{
    swap(d_sourceIP, d_destIP);
    swap(d_sourcePort, d_destPort);
    swap(d_sentBytes, d_receivedBytes);
}
