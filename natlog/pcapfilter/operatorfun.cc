#include "pcapfilter.ih"

void PcapFilter::operator()()
{ 
        // The current PcapFilter object is passed as 1st argument to the
        // callback function, so that PcapFilter::callback can access its
        // object's data

    d_pcap.loop(reinterpret_cast<u_char *>(this), 
                reinterpret_cast<pcap_handler>(callback));
}
