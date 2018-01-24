#include "conntrackrecord.ih"

ConntrackRecord::ConntrackRecord(Protocol type, Pattern const &pattern,
                                 size_t ipHeaderSize)
:
    d_pattern(pattern)
{
    setLastUsed(::time(0));

    setType(pat(CTicmp::TYPE) == "NEW" ? NEW : DESTROY);

    setTime(stoul(pat(CTicmp::SECONDS)), 
            stoul(pat(CTicmp::MU_SECONDS)));

    if (type == ICMP)
        initICMP(pattern, ipHeaderSize);
    else 
        initTCP_UDP(pattern, ipHeaderSize);
}
