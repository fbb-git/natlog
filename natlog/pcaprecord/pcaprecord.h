#ifndef INCLUDED_PCAPRECORD_
#define INCLUDED_PCAPRECORD_

#include <vector>
#include <pcap/pcap.h>
#include <netinet/in.h>

#include <bobcat/inetaddress>

class PcapPacket;

struct PcapRecord
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

    private:
        std::vector<Record> d_connections;

    public:
        struct Address: public FBB::InetAddress
        {
            Address(struct in_addr const &addr, u_short port);
        };

        PcapRecord();
        void add(PcapPacket const &packet);
        void update(PcapPacket const &packet);  // add 'via' address 
        
        time_t seconds(Record const &record) const;        
        suseconds_t microSeconds(Record const &record) const;

        Address sourceIP(Record const &record) const;
        Address viaIP(Record const &record) const;
        Address destIP(Record const &record) const;

    private:
        Record *find(uint32_t sequenceNr);
      
        Address inetAddr(struct in_addr const &addr, u_short port) const;
};

inline PcapRecord::Address::Address(struct in_addr const &addr, u_short port)
:
    FBB::InetAddress( sockaddr_in{0, port, addr} )
{}

inline time_t PcapRecord::seconds(Record const &record) const
{
    return record.beginTime.ts.tv_sec;
}
        
inline suseconds_t PcapRecord::microSeconds(Record const &record) const
{
    return record.beginTime.ts.tv_usec;
}

inline PcapRecord::Address PcapRecord::sourceIP(Record const &record) const
{
    return inetAddr(record.source.addr, record.source.port);
}

inline PcapRecord::Address PcapRecord::viaIP(Record const &record) const
{
    return inetAddr(record.via.addr, record.via.port);
}

inline PcapRecord::Address PcapRecord::destIP(Record const &record) const
{
    return inetAddr(record.dest.addr, record.dest.port);
}

inline PcapRecord::Address PcapRecord::inetAddr(struct in_addr const &addr, 
                                                u_short port) const
{
    return Address(addr, port);
}
        
#endif






