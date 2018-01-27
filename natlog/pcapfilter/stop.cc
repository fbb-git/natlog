#include "pcapfilter.ih"

void PcapFilter::stop()
{
    d_stop = true;
    d_pcap.stop();
}

