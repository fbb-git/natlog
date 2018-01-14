#include "pcaprecord.ih"

PcapRecord::PcapRecord(Type inOut, 
                       struct pcap_pkthdr const &hdr, u_char const *packet)
:
    Record(inOut, hdr.ts.tv_sec, hdr.ts.tv_usec)
{
    setSourceIP(get<IP_Header>(packet).sourceAddr.s_addr);
    setDestIP(get<IP_Header>(packet).destAddr.s_addr);

                                            // hdrLength itself selects its
                                            // bits
    size_t headerLength = get<IP_Header>(packet).hdrLength << 2;
    size_t ipLength = ntohs(get<IP_Header>(packet).length);

        // 4 most significant bits: # 32 bit words
        // so: shr 4 to het the # 32 bit words, and 
        // << 2 to multiply by 4 to get the #bytes before the data
    size_t dataOffset = get<TCP_Header>(packet).dataOffset >> 4 << 2;


    Protocol protocol = static_cast<Protocol>(
                                get<IP_Header>(packet).protocol);
    setProtocol(protocol);

    size_t payloadLength = 0;       // avoids warning with -O2

    switch (protocol)
    {
        case ICMP:
            setKey(ntohs(get<ICMP_Header>(packet).ident));
            payloadLength = ipLength - headerLength;
        break;

        case UDP:
        {
            setPorts(
                ntohs(get<UDP_Header>(packet).sourcePort),
                ntohs(get<UDP_Header>(packet).destPort)
            );
            setTCPUDPkey();

            payloadLength = ntohs(get<UDP_Header>(packet).length) 
                                                    - sizeof(UDP_Header);
        }
        break;

        case TCP:
            setPorts(
                ntohs(get<UDP_Header>(packet).sourcePort),
                ntohs(get<UDP_Header>(packet).destPort)
            );
            setSequenceNr(get<TCP_Header>(packet).sequenceNr);
            setFlags(get<TCP_Header>(packet).flags);

            payloadLength = ipLength - headerLength - dataOffset;

        break;
    }

    setPayload(payloadLength);
}









