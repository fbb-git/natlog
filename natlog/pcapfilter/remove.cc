#include "pcapfilter.ih"

static PcapRecord empty;

void PcapFilter::remove(size_t idx)
{
    delete d_connections[idx];
    d_connections[idx] = &empty;
}
