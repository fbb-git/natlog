#include "pcapfilter.ih"

void PcapFilter::outICMP(PcapPacket const &packet)
{
    size_t findIdx = d_connections.find(packet.id())

    if (findIdx == numeric_limits<size_t>::max())       // not yet registered
        return;

    if (packet.destIP() == d_connections[findIdx].destIP())
        d_connections[findIdx].setViaIP(packet.sourceIP());
}
