#include "pcaprecord.ih"

size_t PcapRecord::find(uint32_t sequenceNr)
{
    size_t idx = 0;
    for (auto &record: d_connections)
    {
        if (record && record->sequenceNr == sequenceNr)
            return idx;
        ++idx;
    }
    return numeric_limits<size_t>::max();
}
