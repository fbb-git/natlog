#include "pcapfilter.ih"

void PcapFilter::callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                          u_char const *packetBytes)
{
    PcapPacket packet(*hdr, packetBytes);

    if (pf->d_type == IN)
        pf->inDevice(packet);
    else 
        pf->outDevice(packet);

//    PcapPacket::TCP_Flags flags = packet.flags();
//
//    bool open = (flags == (PcapPacket::SYN | PcapPacket::ACK));
//    if (open || (flags == (PcapPacket::FIN | PcapPacket::ACK)))
//        cout << packet.seconds() << ':' << packet.microSeconds() << ' ' <<
//                src.dottedDecimalAddress() << " (" << src.port() << "), " <<
//                dst.dottedDecimalAddress() << " (" << dst.port() << "): " <<
//                (open ? "OPEN" : "CLOSE") << '\n';
}

//    PcapPacket::Address &&src = packet.sourceIP();
//    PcapPacket::Address &&dst = packet.destIP();

