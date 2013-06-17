#include "pcapfilter.ih"

void PcapFilter::signalHandler(size_t signum)
{
    d_pcap.stop();
}
