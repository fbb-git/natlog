#include "pcapfilter.ih"

void PcapFilter::outDevice(PcapPacket const &packet)
{
    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
    {
            // The destination address on the OUT device must be 
            // the device's IP address.
            // But how are we going to filter connections that originated
            // from the source-natting host?

        if (packet.destAddr().s_addr != d_pcap.ipAddr())
            return;

        PcapPacket::Address &&dst = packet.destIP();
        PcapPacket::Address &&src = packet.sourceIP();

        cout << "OUTDEVICE: " << packet.flags() << ' ' << 
            packet.sequenceNr() << ". " <<
            packet.seconds() << ':' << packet.microSeconds() << ' ' <<
            src.dottedDecimalAddress() << " (" << src.port() << "), " <<
            dst.dottedDecimalAddress() << " (" << dst.port() << ")" << endl;

        saveAdd(packet);       // via and dest are available
    }
}
