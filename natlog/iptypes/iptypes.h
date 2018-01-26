#ifndef INCLUDED_IPSTRUCTS_
#define INCLUDED_IPSTRUCTS_

#include <arpa/inet.h>

// typedef uint32_t in_addr_t;
// struct in_addr {
//     uint32_t s_addr;  // load with inet_aton()
// };

struct IP_Types
{
    enum Protocol       // update record/protocolstr.cc when modified
    {
        ICMP =  1,
        TCP  =  6,
        UDP  = 17
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
        TCP_Flags_MASK = (CWR << 1) - 1
    };

   enum class IP_Fragment
    {
        RESERVED =          0x8000,
        DONT_FRAGMENT =     0x4000,
        MORE_FRAGMENTS =    0x2000,
        MASK =              0x1fff
    };

    struct Ethernet_Header      // http://en.wikipedia.org/wiki/EtherType
    {
        u_char destMac[6];      // Destination host MAC address
        u_char srcMac[6];       // Source host MAC address
        u_short ether_type;     // IP? ARP? RARP? etc 
    };
    
    struct IP_Header 
    {
        u_char  hdrLength:4,        // in 4-byte words
                version:4;
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

    struct UDP_Header               // udp header length: 8 bytes
    {
         u_short sourcePort;
         u_short destPort;
         u_short length;
         u_short checkSum;
    };                              

    struct ICMP_Header 
    {
        u_char  type;
        u_char  code;
        u_short chksum;
        u_short ident;
        u_short seqnum;

    };                              // icmp header length: 8 bytes

    enum Offsets                // offsets to the various headers
    {                           // the Ethernet header starts at `d_packet'
        ETHER_OFFSET =  0,       
        IP_OFFSET =     ETHER_OFFSET + sizeof(Ethernet_Header),
        TCP_OFFSET =    IP_OFFSET + sizeof(IP_Header),
        UDP_OFFSET =    TCP_OFFSET,
        ICMP_OFFSET =   TCP_OFFSET,
    };

    enum SizeofTCPheader
    {
        SIZEOF_ETHERNET_HEADER = IP_OFFSET,
    };

    template <typename Type>
    static Type const &get(u_char const *packet);
};

//static
template <>
inline IP_Types::IP_Header const &IP_Types::get(u_char const *packet) 
{
    return *reinterpret_cast<IP_Header const *>(packet + IP_OFFSET);
}

//static
template <>
inline IP_Types::TCP_Header const &IP_Types::get(u_char const *packet)
{
    return *reinterpret_cast<TCP_Header const *>(packet + TCP_OFFSET);
}

//static
template <>
inline IP_Types::UDP_Header const &IP_Types::get(u_char const *packet)
{
    return *reinterpret_cast<UDP_Header const *>(packet + UDP_OFFSET);
}
        
//static
template <>
inline IP_Types::ICMP_Header const &IP_Types::get(u_char const *packet)
{
    return *reinterpret_cast<ICMP_Header const *>(packet + ICMP_OFFSET);
}

#endif
