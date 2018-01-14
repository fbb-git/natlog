#include "pcapfilter.ih"

void PcapFilter::inICMP(PcapPacket const &packet)
{
    size_t findIdx = find(packet.id());

    if (findIdx == numeric_limits<size_t>::max())
        addICMP(packet);
                                        // icmp connection completed
    else if (packet.destIP() == d_connections[findIdx].sourceIP())
    {
        d_connections[findIdx].setInBytes(packet.payloadLength());
        logICMP(*d_connections[findIdx]);
        remove(findIdx);
    }

}
