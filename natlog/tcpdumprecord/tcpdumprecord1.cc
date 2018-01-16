#include "tcpdumprecord.ih"

TcpdumpRecord::TcpdumpRecord(Type inOut, PktHdr const &hdr, 
                             u_char const *packet)
:
    Record(inOut, hdr.seconds, hdr.muSeconds, packet)
{
    auto [headerLength, ipLength, dataOffset, payloadLength] = 
                                                        stdLengths(packet);

CERR << (inOut == IN ? "IN" : "OUT") <<
" from: " << sourceIPstr() << " to " << destIPstr() << '\n';

    switch (protocol())
    {
        case ICMP:
            setKey(ntohs(get<ICMP_Header>(packet).ident));
            payloadLength =  ipLength - headerLength;   //  - dataOffset;
        break;

        case UDP:
        {                               // already in host byte order
            setPorts(
                ntohs(get<UDP_Header>(packet).sourcePort),
                ntohs(get<UDP_Header>(packet).destPort)
            );
            setID(ntohs(get<IP_Header>(packet).identification));

                                        // already in host byte order           
            payloadLength = ntohs(get<UDP_Header>(packet).length)
                                                        - sizeof(UDP_Header);
        }
        break;

        case TCP:
            setPorts(
                get<UDP_Header>(packet).sourcePort,
                get<UDP_Header>(packet).destPort
            );
            setID(get<TCP_Header>(packet).sequenceNr);
            setFlags(get<TCP_Header>(packet).flags);

            payloadLength = ipLength - headerLength - dataOffset;
        break;
    }

    setPayload(payloadLength);
}






