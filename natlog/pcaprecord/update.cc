#include "pcaprecord.ih"

void PcapRecord::update(PcapPacket const &packet)
{
    if (Record *record = find(packet.sequenceNr()))
    {
        record->via = {packet.sourceAddr(), packet.sourcePort()};

        Address &&src = sourceIP(*record);
        Address &&via = viaIP(*record);
        Address &&dst = destIP(*record);

        cout << seconds(*record) << ':' << microSeconds(*record) << 
                " from " <<
                    src.dottedDecimalAddress() << " (" << src.port() << "), " 
                "via " <<
                    via.dottedDecimalAddress() << " (" << via.port() << "), "
                "to " <<
                    dst.dottedDecimalAddress() << " (" << dst.port() << 
                ")\n";
    }
}

