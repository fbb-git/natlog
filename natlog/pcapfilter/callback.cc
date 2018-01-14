#include "pcapfilter.ih"

// static
void PcapFilter::callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                          u_char const *packet)
{
        // packet begin is subtracted because the ethernet header is assumed
        // present. If it's not then a correction the size of the ethernet
        // header is required when using the offsets below 
    packet -= pf->shiftPacketBegin();

    if (pf->d_options.hasProtocol(
                IP_Types::get<IP_Types::IP_Header>(packet).protocol)
    )
        pf->d_storage.push( PcapRecord{ pf->d_type, *hdr, packet } );
}
