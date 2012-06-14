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
            cout << "Remove #" << idx << ":    ";
            display(element);
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

