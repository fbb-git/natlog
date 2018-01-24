#include "conntrackrecord.ih"

void ConntrackRecord::initICMP(Pattern const &pattern, size_t ipHeaderSize)
{
    setSourceIP( aton(pat(CTicmp::SRC))    );
    setDestIP(   aton(pat(CTicmp::DST))    );
    setViaIP(    aton(pat(CTicmp::NATSRC)) );

    setProtocol(ICMP);
    setKey( stoul(pat(CTicmp::ID)) );

    if (type() == DESTROY)
    {
        if (pattern.end() == static_cast<size_t>(CTicmp::nFields))
        {
            if (ipHeaderSize)
                ipHeaderSize *= stoul(pat(CTicmp::RECVDPACKETS));

            size_t nBytes = stoul(pat(CTicmp::SENTBYTES));
            addSentBytes( nBytes ? nBytes - ipHeaderSize : 0 );

            nBytes = stoul(pat(CTicmp::RECVDBYTES));
            addReceivedBytes( nBytes ? nBytes - ipHeaderSize : 0 ); 

        }
    };
}
