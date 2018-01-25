#include "pcap.ih"

void Pcap::loop(void *pcapFilterPtr, pcap_handler callback)
{
    pcap_loop(d_pcap, -1, callback, 
              reinterpret_cast<u_char *>(pcapFilterPtr));
}

// Pcap::loop: merely calls pcap_loop: 
//     * 1st argument pointer to the PcapFilter object defining the current
//              Pcap object as data member
//     * 2nd arg: continue until the program ends
//     * 3rd arg: PcapFilter::callback
//     * 4th arg. the address of the PcapFilter object is passed to callback
