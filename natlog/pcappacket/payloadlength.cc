#include "pcappacket.ih"

size_t PcapPacket::payloadLength() const
{
    return ipLength() - headerLength() - dataOffset();
}
