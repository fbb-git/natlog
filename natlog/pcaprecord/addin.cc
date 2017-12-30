#include "pcaprecord.ih"

// See ../tcpdump.nat: a SYN/ACK packet was received from the destination, so
//  the record's source is the remote (at the OUT interface) destination
//  address and record's destination is the source address (at the IN
//  interface) which has been natted by the firewall: 
// IN.source = record.dest = IN.dest = record.src

void PcapRecord::addIn(PcapPacket const &packet)
{
            // the record has already been seen at the OUT interface?
    size_t idx = find(packet.sequenceNr());

    if (idx != numeric_limits<size_t>::max())   // known record
    {
        Record *record = d_connections[idx];

                            // then assign the record's source IP/port:
        record->source = {packet.destAddr(), packet.destPort()};
        record->status = ESTABLISHED;
        record->inBytes += packet.length();     // add #bytes for this conn.

        imsg << "Add #" << idx << endl;
        display(imsg, record) << FBB::endl;
    }
    else                    // else store a new record.
        store(
                new Record 
                {
                    INCOMPLETE,
                    packet.timeval(), 
                    {packet.destAddr(), packet.destPort()},
                    {{0}, 0},
                    {packet.sourceAddr(), packet.sourcePort()},
                    packet.sequenceNr(),
                    packet.length(),            // inBytes
                    0                           // outBytes
                }
        );
}




