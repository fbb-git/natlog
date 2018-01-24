#include "pcapfilter.ih"

void PcapFilter::operator()()
{ 
        // The current PcapFilter object is passed as 1st argument to the
        // callback function, so that PcapFilter::callback can access its
        // object's data. the 'callback' cast is used because Pcap has no
        // knowledge about PcapFilter, and only needs to call the C function
        // pcap_loop.

    d_pcap.loop(this, reinterpret_cast<pcap_handler>(callback));
}
