#include "tcpdumprecord.ih"

TcpdumpRecord::TcpdumpRecord(Type inOut, PktHdr const &hdr, 
                             u_char const *packet)
:
    Record(inOut, hdr.seconds, hdr.muSeconds, packet)
{}






