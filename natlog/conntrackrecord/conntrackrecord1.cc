#include "conntrackrecord.ih"

ConntrackRecord::ConntrackRecord(Protocol type, Pattern const &pattern)
:
    d_pattern(pattern)
{
    setLastUsed(::time(0));
    
    setType(pat(CTicmp::TYPE) == "NEW" ? NEW : DESTROY);

    setAllTimes(stoul(pat(CTicmp::SECONDS)), 
                stoul(pat(CTicmp::MU_SECONDS)));

    if (type == ICMP)
        initICMP(pattern);
    else 
        initTCP_UDP(pattern);
}
