#include "pcapfilter.ih"

void PcapFilter::saveAdd(PcapPacket const &packet)
{
    lock_guard<mutex> guard(s_recordMutex);

    d_record.add(packet, d_type);
}
