#include "pcapfilter.ih"

void PcapFilter::signaled(size_t signum)
{
    d_pcap.stop();
}
