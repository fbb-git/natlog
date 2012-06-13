#include "pcaprecord.ih"

void PcapRecord::add(PcapPacket const &packet)
{
    d_connections.push_back(
            {
                packet.timeval(), 
                {packet.sourceAddr(), packet.sourcePort()},
                {{0}, 0},
                {packet.destAddr(), packet.destPort()},
                packet.sequenceNr()
            }
    );
}
