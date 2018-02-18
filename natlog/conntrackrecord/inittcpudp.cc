#include "conntrackrecord.ih"

void ConntrackRecord::initTCP_UDP(Pattern const &pattern)
{
    setSourceIP( aton(pat(CTtcpudp::SRC))   );
    setDestIP(  aton(pat(CTtcpudp::DST))    );
    setViaIP(   aton(pat(CTtcpudp::NATSRC)) );

    setPorts( stoul(pat(CTtcpudp::SPORT)), stoul(pat(CTtcpudp::DPORT)) );
    setViaPort( stoul(pat(CTtcpudp::NATPORT)) );

    setProtocol( pat(CTtcpudp::PROTOCOL) == "tcp" ? TCP : UDP );

    setSrcKey();

    if (type() == DESTROY)      // DESTROY records may have sent/received
    {                           //                              byte counts
        if (pattern.end() == static_cast<size_t>(CTtcpudp::nFields))
        {
            size_t ipHeaderSize =  Options::instance().IPheaderSize();
            if (ipHeaderSize != 0)
                ipHeaderSize *= stoul(pat(CTtcpudp::RECVDPACKETS));

            size_t nBytes = stoul(pat(CTtcpudp::SENTBYTES));
            setSentBytes( nBytes ? nBytes - ipHeaderSize : 0 );

            nBytes = stoul(pat(CTtcpudp::RECVDBYTES));
            setReceivedBytes( nBytes ? nBytes - ipHeaderSize : 0 ); 
        }
    };
}
