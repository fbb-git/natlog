#include "pcaprecord.ih"

PcapRecord::Record *PcapRecord::find(uint32_t sequenceNr)
{
    for (auto &record: d_connections)
    {
        if (record.sequenceNr == sequenceNr)
            return &record;
    }

    return 0;
}
