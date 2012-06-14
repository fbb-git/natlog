#include "pcapfilter.ih"

void PcapFilter::outDevice(PcapPacket const &packet)
{
    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
        saveAdd(packet);       // via and dest are available
}

