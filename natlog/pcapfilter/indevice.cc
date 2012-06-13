#include "pcapfilter.ih"

void PcapFilter::inDevice(PcapPacket const &packet)
{
    PcapPacket::Address &&src = packet.sourceIP();
    PcapPacket::Address &&dst = packet.destIP();

    cout << packet.seconds() << ':' << packet.microSeconds() << ' ' <<
            src.dottedDecimalAddress() << " (" << src.port() << "), " <<
            dst.dottedDecimalAddress() << " (" << dst.port() << ")" << endl;

    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
        saveAdd(packet);
}
