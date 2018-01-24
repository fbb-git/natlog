#include "pcapfilter.ih"

PcapFilter::PcapFilter(char const *device, Record::Type type, 
                       std::ostream &stdMsg, Storage &storage) 
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_type(type),
    d_pcap(device)  // see pcap.h for default arg. specs.
{
    if (type == Record::OUT)
        handleSignals();
}
