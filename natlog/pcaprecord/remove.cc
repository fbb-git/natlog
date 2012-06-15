#include "pcaprecord.ih"

void PcapRecord::remove(PcapPacket const &packet)
{
    size_t idx = 0;

    for (auto &element: d_connections)
    {
        if (
            element != 0
            &&
            element->source.port == packet.sourcePort()
            &&
            memcmp(&element->source.addr, &packet.sourceAddr(), 
                    sizeof(struct in_addr)) == 0
        )
        {
            imsg << "Rem #" << idx << endl;
            log(element, packet.seconds(), packet.microSeconds());
            delete element;
            element = 0;
            return;
        }
        ++idx;
    }

//    cout << "FIN/ACK: no record for " << 
//            packet.sourceIP().dottedDecimalAddress() << 
//            " (" << packet.sourcePort() << ") to " <<
//            packet.destIP().dottedDecimalAddress() << 
//            " (" << packet.destPort() << ')' << endl;
}

