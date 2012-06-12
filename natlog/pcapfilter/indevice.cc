#include "pcapfilter.ih"

void PcapFilter::inDevice(PcapPacket const &packet)
{
    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
        saveAdd(packet);
}
