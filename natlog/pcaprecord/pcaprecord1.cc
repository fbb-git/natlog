#include "pcaprecord.ih"

PcapRecord::PcapRecord(Type inOut, 
                       struct pcap_pkthdr const &hdr, u_char const *packet)
:
    Record(inOut, hdr.ts.tv_sec, hdr.ts.tv_usec, packet)
{
    auto [headerLength, ipLength, dataOffset, payloadLength] = 
                                                        stdLengths(packet);

    switch (protocol())
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
            setID(ntohs(get<IP_Header>(packet).identification));

            payloadLength = ntohs(get<UDP_Header>(packet).length) 
                                                    - sizeof(UDP_Header);
        }
        break;

        case TCP:
            setPorts(
                ntohs(get<UDP_Header>(packet).sourcePort),
                ntohs(get<UDP_Header>(packet).destPort)
            );
            setID(get<TCP_Header>(packet).sequenceNr);
            setFlags(get<TCP_Header>(packet).flags);

            payloadLength = ipLength - headerLength - dataOffset;

        break;
    }

    setPayload(payloadLength);
}









