#ifndef INCLUDED_CONNTRACKRECORD_
#define INCLUDED_CONNTRACKRECORD_

// CTtcpudp and CTicmp: see below

#include <iosfwd>

#include "../record/record.h"

namespace FBB
{
    class Pattern;
}

class ConntrackRecord: public Record
{
    FBB::Pattern const &d_pattern;
            
    public:
        ConntrackRecord(Protocol protocol, FBB::Pattern const &pattern,
                        size_t ipHeaderSize);

    private:
        void initTCP_UDP(FBB::Pattern const &pattern, size_t ipHeaderSize);
        void initICMP(FBB::Pattern const &pattern, size_t ipHeaderSize);

        template <typename Enum>
        std::string pat(Enum value) const;
};

    // Indices when matching conntrackproducer entries with Pattern for tcp/udp
enum class CTtcpudp
{
    SECONDS = 1,    // 1st three entries are common with CTicmp
    MU_SECONDS,              
    TYPE,           // NEW, DESTROY

    PROTOCOL,       // tcp/udp
    SRC,
    DST,
    SPORT,
    DPORT,
    SENTPACKETTEXT,
    SENTPACKETS,
    SENTBYTES,
    NATSRC,
    NATPORT,
    RECVDPACKETTEXT,
    RECVDPACKETS,
    RECVDBYTES,
    nFields,
};
    
    // Indices when matching conntrackproducer entries with Pattern for tcp/udp
enum class CTicmp
{
    SECONDS   =   1,
    MU_SECONDS,              
    TYPE,       // NEW, DESTROY

    SRC,
    DST,
    ID,
    SENTPACKETTEXT,
    SENTPACKETS,
    SENTBYTES,
    NATSRC,
    RECVDPACKETTEXT,
    RECVDPACKETS,
    RECVDBYTES,
    nFields,
};
    
#endif
