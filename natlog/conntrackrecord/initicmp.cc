#include "conntrackrecord.ih"

void ConntrackRecord::initICMP(Pattern const &pattern)
{
    setSourceIP( aton(pat(CTicmp::SRC))    );
    setDestIP(   aton(pat(CTicmp::DST))    );
    setViaIP(    aton(pat(CTicmp::NATSRC)) );

    setProtocol(ICMP);
    setKey( stoul(pat(CTicmp::ID)) );

CERR << lastUsed() << '\n';

    if (type() == DESTROY)
    {
        if (pattern.end() == static_cast<size_t>(CTicmp::nFields))
        {
            addSentBytes(     stoul(pat(CTicmp::SENTBYTES))  );
            addReceivedBytes( stoul(pat(CTicmp::RECVDBYTES)) ); 
        }
    };
}
