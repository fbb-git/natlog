#include "pcap.ih"

void Pcap::stop()
{
    pcap_breakloop(d_pcap);     // ends pcap_loop, 
    pcap_close(d_pcap);
}

