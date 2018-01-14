#include "pcapfilter.ih"

void PcapFilter::outDevice(PcapPacket const &packet)
{
    switch (packet.protocol())
    {
        case PcapRecord::ICMP:
            outICMP(packet);
        break;

        default:
        break;

    }
}

//    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))
//        saveAdd(packet);       // via and dest are available


