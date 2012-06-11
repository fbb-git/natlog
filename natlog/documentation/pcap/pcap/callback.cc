#include "pcap.ih"

void Pcap::callback(u_char *user, struct pcap_pkthdr const *hdr,
                    u_char const *bytes)
{
    PcapPacket packet(*hdr, bytes);

    PcapPacket::Address &&src = packet.sourceIP();
    PcapPacket::Address &&dst = packet.destIP();

    PcapPacket::TCP_Flags flags = packet.flags();

    bool open = (flags == (PcapPacket::SYN | PcapPacket::ACK));
    if (open || (flags == (PcapPacket::FIN | PcapPacket::ACK)))
        cout << packet.seconds() << ':' << packet.microSeconds() << ' ' <<
                src.dottedDecimalAddress() << " (" << src.port() << "), " <<
                dst.dottedDecimalAddress() << " (" << dst.port() << "): " <<
                (open ? "OPEN" : "CLOSE") << '\n';
}
