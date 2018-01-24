#include "pcap.ih"

void Pcap::loop(void *pcapFilterPtr, pcap_handler callback)
{
    pcap_loop(d_pcap, -1, callback, 
              reinterpret_cast<u_char *>(pcapFilterPtr));
}
