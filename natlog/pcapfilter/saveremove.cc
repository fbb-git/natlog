#include "pcapfilter.ih"

void PcapFilter::saveRemove(PcapPacket const &packet)
{
    lock_guard<mutex> guard(s_recordMutex);

    d_record.remove(packet);
}
