#include "pcapfilter.ih"

void PcapFilter::callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                          u_char const *packetBytes)
{
    PcapPacket packet(*hdr, packetBytes - pf->shiftPacketBegin());

    if (pf->d_type == PcapRecord::IN)
        pf->inDevice(packet);
    else 
        pf->outDevice(packet);
}
