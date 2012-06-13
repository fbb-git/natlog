#include "pcapfilter.ih"

void PcapFilter::inDevice(PcapPacket const &packet)
{
    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
    {
        PcapPacket::Address &&src = packet.sourceIP();
        PcapPacket::Address &&dst = packet.destIP();

        cout << "INDEVICE: " << packet.flags() << ' ' << 
            packet.sequenceNr() << ". " <<
            packet.seconds() << ':' << packet.microSeconds() << ' ' <<
            src.dottedDecimalAddress() << " (" << src.port() << "), " <<
            dst.dottedDecimalAddress() << " (" << dst.port() << ")" << endl;

        saveAdd(packet);    // src and dest are available
    }
}
