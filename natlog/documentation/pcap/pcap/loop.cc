#include "pcap.ih"

void Pcap::loop()
{
    pcap_loop(d_pcap, -1, callback, 0);
}
