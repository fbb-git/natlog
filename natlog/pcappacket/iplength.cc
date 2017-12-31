#include "pcappacket.ih"

size_t PcapPacket::ipLength() const
{
    return ntohs(get<IP_Header>().length);
}
