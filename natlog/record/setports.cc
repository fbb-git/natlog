#include "record.ih"

void Record::setPorts(size_t sourcePort, size_t destPort)
{
    d_sourcePort = sourcePort;
    d_destPort = destPort;
}
