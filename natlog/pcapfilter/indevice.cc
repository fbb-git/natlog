#include "pcapfilter.ih"

void PcapFilter::inDevice(PcapPacket const &packet)
{
    switch (packet.protocol())
    {
        case PcapRecord::ICMP:
            inICMP(packet);
        break;

        default:
        break;
}

//
//
//    if (packet.flags(PcapPacket::SYN | PcapPacket::ACK))    // SYN *and* ACK
//        saveAdd(packet);                    // src and dest are available
//
//                                                            // FIN *and* ACK
//    else if (packet.flags(PcapPacket::FIN | PcapPacket::ACK))
//        saveRemove(packet);    
//}
//


