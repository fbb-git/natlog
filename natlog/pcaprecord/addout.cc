#include "pcaprecord.ih"

// See ../tcpdump.nat: a SYN/ACK packet was received from the destination, so
//  the record's source is the remote (at the OUT interface) destination
//  address and record's destination is the natted address (i.e., the `via'
//  address, which is the IP address of the firewalling host):
// OUT.source = record.dest  and OUT.dest = record.via

void PcapRecord::addOut(PcapPacket const &packet)
{
            // the record has already been seen at the OUT interface?
            // the record has already been seen at the OUT interface?
    size_t idx = find(packet.sequenceNr());

    if (idx != numeric_limits<size_t>::max())
    {
        Record *record = d_connections[idx];

                            // then assign the record's `via' IP/port:
        record->via = {packet.destAddr(), packet.destPort()};
        record->status = ESTABLISHED;
        imsg << "Add OUT #" << idx << endl;
        display(imsg, record) << FBB::endl;
    }
    else                    // else store a new record.
        store(
                new Record
                {
                    INCOMPLETE,
                    packet.timeval(), 
                    {{0}, 0},
                    {packet.destAddr(), packet.destPort()},
                    {packet.sourceAddr(), packet.sourcePort()},
                    packet.sequenceNr()
                }
        );
}




