#include "pcaprecord.ih"

void PcapRecord::add(PcapPacket const &packet, Type type)
{
//    cerr << "Device " << type << ", Packet flags: " << hex << packet.flags() << '\n';

    if (type == IN)
        addIn(packet);
    else
        addOut(packet);
}

