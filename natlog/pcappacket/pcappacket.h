#ifndef INCLUDED_PCAPPACKET_
#define INCLUDED_PCAPPACKET_

#include <pcap.h>
#include <bobcat/inetaddress>

class PcapPacket
{
    struct pcap_pkthdr const &d_hdr;    // struct timeval: see gettimeofday(2)
    u_char const *d_packet;             // the captured packet

    struct Ethernet_Header      // http://en.wikipedia.org/wiki/EtherType
    {
        u_char destMac[6];      // Destination host MAC address
        u_char srcMac[6];       // Source host MAC address
        u_short ether_type;     // IP? ARP? RARP? etc 
    };

    enum class IP_Fragment
    {
        RESERVED =          0x8000,
        DONT_FRAGMENT =     0x4000,
        MORE_FRAGMENTS =    0x2000,
        MASK =              0x1fff
    };
    struct IP_Header 
    {
        u_char versionHdrLength;    // version << 4 | header length >> 2 
        u_char tos;                 // type of service
        u_short length;             // total length 
        u_short identification;
        u_short fragmentOffset;
        u_char  timeToLive;
        u_char  protocol;
        u_short checkSum;
        struct in_addr sourceAddr;
        struct in_addr destAddr;
    };

    struct TCP_Header 
    {
        u_short sourcePort;
        u_short destPort;
        uint32_t sequenceNr;
        uint32_t ackNumber;

        u_char dataOffset;          // data offset, 
                                    // (((th)->th_offx2 & 0xf0) >> 4)
        u_char flags;
        u_short window;
        u_short checkSum;
        u_short urgentPtr;
    };

    enum Offsets                // offsets to the various headers
    {                           // the Ethernet header starts at `d_packet'
        ETHER_OFFSET =  0,       
        IP_OFFSET =     ETHER_OFFSET + sizeof(Ethernet_Header),
        TCP_OFFSET =    IP_OFFSET + sizeof(IP_Header),
        DATA_OFFSET =   TCP_OFFSET + sizeof(TCP_Header)
    };

    public:
        enum SizeofTCPheader
        {
            SIZEOF_TCP_HEADER = DATA_OFFSET
        };

        enum TCP_Flags
        {
            FIN  = 0x01,
            SYN  = 0x02,
            RST  = 0x04,
            PUSH = 0x08,
            ACK  = 0x10,
            URG  = 0x20,
            ECE  = 0x40,
            CWR  = 0x80,
            TCP_Flags_MASK = FIN | SYN | RST | ACK | URG | ECE | CWR
        };
        struct Address: public FBB::InetAddress
        {
            Address(struct in_addr const &addr, u_short port);
        };

        PcapPacket(struct pcap_pkthdr const &hdr, u_char const *packet);

        time_t seconds() const;
        suseconds_t microSeconds() const;
  
        Address sourceIP() const;
        Address destIP() const;
        TCP_Flags flags() const;

    private:
        template <typename Type>
        Type const &get() const;

        Address inetAddr(struct in_addr const &addr, u_short port) const;
};

template <>
inline PcapPacket::IP_Header const &PcapPacket::get() const
{
    return *reinterpret_cast<IP_Header const *>(d_packet + IP_OFFSET);
}

template <>
inline PcapPacket::TCP_Header const &PcapPacket::get() const
{
    return *reinterpret_cast<TCP_Header const *>(d_packet + TCP_OFFSET);
}


inline PcapPacket::Address::Address(struct in_addr const &addr, u_short port)
:
    FBB::InetAddress( sockaddr_in{0, port, addr} )
{}

inline PcapPacket::TCP_Flags PcapPacket::flags() const
{
    u_char ret = get<TCP_Header>().flags;
    return static_cast<TCP_Flags>(ret);
}
        
inline time_t PcapPacket::seconds() const
{
    return d_hdr.ts.tv_sec;
}
        
inline suseconds_t PcapPacket::microSeconds() const
{
    return d_hdr.ts.tv_usec;
}

inline PcapPacket::Address PcapPacket::sourceIP() const
{
    return 
        inetAddr(get<IP_Header>().sourceAddr, get<TCP_Header>().sourcePort);
}

inline PcapPacket::Address PcapPacket::destIP() const
{
    return 
        inetAddr(get<IP_Header>().destAddr, get<TCP_Header>().destPort);
}

inline PcapPacket::Address PcapPacket::inetAddr(struct in_addr const &addr, 
                                                u_short port) const
{
    return Address(addr, port);
}
        
#endif


