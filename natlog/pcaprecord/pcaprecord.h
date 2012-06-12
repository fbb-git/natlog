#ifndef INCLUDED_PCAPRECORD_
#define INCLUDED_PCAPRECORD_

#include <vector>
#include <pcap/pcap.h>
#include <netinet/in.h>

class PcapPacket;

class PcapRecord
{
    struct AddrPort
    {
        struct in_addr addr;
        u_short port;
    };
    struct Record
    {
        struct pcap_pkthdr  beginTime;
        AddrPort            source;
        AddrPort            via;
        AddrPort            dest;
        uint32_t            sequenceNr;
    };
    std::vector<Record> d_connections;

    public:
        PcapRecord();
        void add(PcapPacket const &packet);

    private:
};
        
#endif






