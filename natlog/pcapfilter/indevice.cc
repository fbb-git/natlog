#include "pcapfilter.ih"

void PcapFilter::inDevice(PcapPacket const &packet)
{
    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
        saveAdd(packet);    // src and dest are available
    else if (packet.flags(PcapPacket::FIN | PcapPacket::ACK))
        saveRemove(packet);    
}



