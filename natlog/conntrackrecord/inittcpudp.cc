#include "conntrackrecord.ih"

void ConntrackRecord::initTCP_UDP(Pattern const &pattern)
{
    setSourceIP( aton(pat(CTtcpudp::SRC))   );
    setDestIP(  aton(pat(CTtcpudp::SRC))    );
    setViaIP(   aton(pat(CTtcpudp::NATSRC)) );

    setPorts( stoul(pat(CTtcpudp::SPORT)), stoul(pat(CTtcpudp::DPORT)) );
    setViaPort( stoul(pat(CTtcpudp::NATPORT)) );

    setProtocol( pat(CTtcpudp::PROTOCOL) == "tcp" ? TCP : UDP );

    setTCPUDPkey();

    if (type() == DESTROY)      // DESTROY records may have sent/received
    {                           //                              byte counts

        if (pattern.end() == static_cast<size_t>(CTtcpudp::nFields))
        {
            addSentBytes(     stoul(pat(CTtcpudp::SENTBYTES))  );
            addReceivedBytes( stoul(pat(CTtcpudp::RECVDBYTES)) ); 
        }
    };
}
