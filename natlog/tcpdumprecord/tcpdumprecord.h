#ifndef INCLUDED_TCPDUMPRECORD_
#define INCLUDED_TCPDUMPRECORD_

#include "../record/record.h"

class TcpdumpRecord: public Record
{
    public:
        struct PktHdr       // this packet hdr is used by captured files.
        {                   // pcap_pkthdr uses `struct timeval ts', which is
                            // longer than 2 x uint32_t
            uint32_t seconds;   // time stamp
            uint32_t muSeconds; // time stamp
        
            uint32_t caplen;    // length of portion present
            uint32_t len;       // length this packet (off wire)
        };

        TcpdumpRecord(Type inOut, PktHdr const &hdr, u_char const *packet);
        // ~TcpdumpRecord() override;
};
        
#endif
