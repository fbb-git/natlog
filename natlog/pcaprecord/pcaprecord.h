#ifndef INCLUDED_PCAPRECORD_
#define INCLUDED_PCAPRECORD_

#include <pcap.h>

#include <netinet/in.h>

#include "../record/record.h"

class PcapRecord: public Record
{
    public:
        PcapRecord(Type inOut, struct pcap_pkthdr const &hdr, 
                   u_char const *packet);
        // ~PcapRecord() override;
};

#endif

