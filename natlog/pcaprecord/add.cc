#include "pcaprecord.ih"

void PcapRecord::add(PcapPacket const &packet, Type type)
{
    if (Record *record = find(packet.sequenceNr()))
    {
        (
            type == IN ?     // already saw: OUT: now fill in the source
                record->source 
            :
                record->via
        ) 
            = {packet.sourceAddr(), packet.sourcePort()};

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
    else
        d_connections.push_back(
            type == IN ?
                Record 
                {
                    packet.timeval(), 
                    {packet.sourceAddr(), packet.sourcePort()},
                    {{0}, 0},
                    {packet.destAddr(), packet.destPort()},
                    packet.sequenceNr()
                }
            :
                Record 
                {
                    packet.timeval(), 
                    {{0}, 0},
                    {packet.sourceAddr(), packet.sourcePort()},
                    {packet.destAddr(), packet.destPort()},
                    packet.sequenceNr()
                }
    );
}




