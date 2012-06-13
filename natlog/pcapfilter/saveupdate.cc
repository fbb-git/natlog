#include "pcapfilter.ih"

void PcapFilter::saveUpdate(PcapPacket const &packet)
{
    lock_guard<mutex> guard(s_recordMutex);
    d_record.update(packet);
}
