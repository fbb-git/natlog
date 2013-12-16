#include "conntrackrecord.ih"

void ConntrackRecord::addIcmp(std::string const &key, Pattern const &pat)
{
    *firstFree() = new Record 
        {key, 
            pat[1], pat[2], "icmp",
            pat[4], pat[5], "", "", pat[7], ""};
        //  src IP  dst IP          snat IP
}
