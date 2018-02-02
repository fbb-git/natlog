#include "pcap.ih"

#include <iomanip>

void Pcap::callback(u_char *pcapPtr, struct pcap_pkthdr const *hdr,
                    u_char const *bytes)
{
    PcapPacket packet(*hdr, bytes - 
                            reinterpret_cast<Pcap *>(pcapPtr)->d_shift);
                                    // use  bytes - 14 for tun0 (vpn)
                                    // which does not have an ethernet header

//    cout << dec;
//    for (size_t idx = 0; idx != PcapPacket::SIZEOF_TCP_HEADER; ++idx)
//        cout << setw(3) << (unsigned)bytes[idx] << ' ';
//    cout << endl;

    PcapPacket::Address &&src = packet.sourceIP();
    PcapPacket::Address &&dst = packet.destIP();

    PcapPacket::TCP_Flags flags = packet.flags();

//    bool open = (flags == (PcapPacket::SYN | PcapPacket::ACK));
//    if (open || (flags == (PcapPacket::FIN | PcapPacket::ACK)))
        cout << dec << 
                packet.seconds() << ':' << packet.microSeconds() << ' ' <<
                src.dottedDecimalAddress() << " (" << src.port() << "), " <<
                dst.dottedDecimalAddress() << " (" << dst.port() << "): " <<
                hex << flags << endl;

                    // (open ? "OPEN" : "CLOSE") << '\n';
}
