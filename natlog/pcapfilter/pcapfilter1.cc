#include "pcapfilter.ih"

PcapFilter::PcapFilter(char const *device, PcapRecord &record, Type type)
:
    d_device(device),
    d_record(record),
    d_type(type),
    d_pcap(device)  // see pcap.h for default arg. specs.
{}
