#include "pcapfilter.ih"

thread_local size_t count = 0;

// static
void PcapFilter::callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                          u_char const *packet)
{
if (pf->d_msg and ++count == 2000)
{
    pf->d_stdMsg << "PcapFilter::callback after 2000 packets\n";
    count = 0;
}

    if (pf->d_stop)
        return;

        // packet begin is subtracted because the ethernet header is assumed
        // present. If it's not then a correction the size of the ethernet
        // header is required when using the offsets below 
    packet -= pf->shiftPacketBegin();

    if (pf->d_options.hasProtocol(
                IP_Types::get<IP_Types::IP_Header>(packet).protocol)
    )
        pf->d_storage.push( PcapRecord{ pf->d_type, *hdr, packet } );
}
