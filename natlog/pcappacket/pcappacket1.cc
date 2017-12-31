#include "pcappacket.ih"

PcapPacket::PcapPacket(struct pcap_pkthdr const &hdr, u_char const *packet) 
:
    d_hdr(hdr),
    d_packet(packet)
{}
