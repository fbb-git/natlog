#include "pcaprecord.ih"

PcapRecord::PcapRecord(Type inOut, 
                       struct pcap_pkthdr const &hdr, u_char const *packet)
:
    Record(inOut, hdr.ts.tv_sec, hdr.ts.tv_usec, packet)
{}









