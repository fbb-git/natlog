#include "pcapfilter.ih"

// static
void PcapFilter::callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                          u_char const *packetBytes)
{
    PcapPacket packet{ *hdr, packetBytes - pf->shiftPacketBegin() };


    if (pf->d_type == PcapRecord::IN)
        pf->inDevice(packet);               // Pre-NAT device
    else 
        pf->outDevice(packet);              // post-NAT device
}
