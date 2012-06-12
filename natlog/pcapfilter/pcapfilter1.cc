#include "pcapfilter.ih"

PcapFilter::PcapFilter(char const *device, PcapRecord &record, Type type)
:
    d_device(device),
    d_record(record),
    d_type(type),
    d_pcap(device, false, PcapPacket::SIZEOF_TCP_HEADER)
{
    d_pcap.filter(s_filterExpr);
}
