#include "record.ih"

Record::Record(Type type, size_t seconds, size_t muSeconds,  
               u_char const *packet)
:
    d_protocol(static_cast<Protocol>(get<IP_Header>(packet).protocol)),
    d_type(type),

    d_seconds(seconds),
    d_microSeconds(muSeconds),
    d_inSeconds(seconds),
    d_inMicroSeconds(muSeconds),

    d_sourceIP(get<IP_Header>(packet).sourceAddr.s_addr),
    d_destIP(get<IP_Header>(packet).destAddr.s_addr),

    d_lastUsed(::time(0))
{
    ++s_count;

    size_t headerLength = size_t(get<IP_Header>(packet).hdrLength << 2);
    size_t ipLength = ntohs(get<IP_Header>(packet).length);

            // 4 most significant bits: # 32 bit words
            // so: shr 4 to het the # 32 bit words, and 
            // << 2 to multiply by 4 to get the #bytes before the data
    size_t dataOffset = size_t(get<TCP_Header>(packet).dataOffset >> 4 << 2);

    switch (protocol())
    {
        case ICMP:
            setIDKey(ntohs(get<ICMP_Header>(packet).ident),
                     ntohs(get<ICMP_Header>(packet).seqnum));
            d_payload = ipLength - headerLength;
        break;

        case UDP:
        {
            setPorts(
                ntohs(get<UDP_Header>(packet).sourcePort),
                ntohs(get<UDP_Header>(packet).destPort)
            );
            d_key.key = ntohs(get<IP_Header>(packet).identification);
            d_payload = ntohs(get<UDP_Header>(packet).length) 
                                                    - sizeof(UDP_Header);
        }
        break;

        case TCP:
            setPorts(
                ntohs(get<UDP_Header>(packet).sourcePort),
                ntohs(get<UDP_Header>(packet).destPort)
            );
            d_key.key = get<TCP_Header>(packet).sequenceNr;
            d_flags = get<TCP_Header>(packet).flags;

            d_payload = ipLength - headerLength - dataOffset;

        break;
    }
}    

