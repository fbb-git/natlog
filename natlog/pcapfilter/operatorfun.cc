#include "pcapfilter.ih"

void PcapFilter::operator()()
{
    d_pcap.loop(reinterpret_cast<u_char *>(this), 
                reinterpret_cast<pcap_handler>(callback));
}
