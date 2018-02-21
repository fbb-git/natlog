#include "conntrackrecord.ih"

void ConntrackRecord::initICMP(Pattern const &pattern)
{
    setSourceIP( aton(pat(CTicmp::SRC))    );
    setDestIP(   aton(pat(CTicmp::DST))    );
    setViaIP(    aton(pat(CTicmp::NATSRC)) );

    setProtocol(ICMP);
    setIDKey( stoul(pat(CTicmp::ID)), 0 );  // no sequence nr available

    if (type() == DESTROY)
    {
        if (pattern.end() == static_cast<size_t>(CTicmp::nFields))
        {
            size_t ipHeaderSize = Options::instance().IPheaderSize();
            if (ipHeaderSize != 0)
                ipHeaderSize *= stoul(pat(CTicmp::RECVDPACKETS));

            size_t nBytes = stoul(pat(CTicmp::SENTBYTES));
            setSentBytes( nBytes ? nBytes - ipHeaderSize : 0 );

            nBytes = stoul(pat(CTicmp::RECVDBYTES));
            setReceivedBytes( nBytes ? nBytes - ipHeaderSize : 0 ); 

        }
    };
}
