#include "conntrackrecord.ih"

void ConntrackRecord::add(std::string const &key, Pattern const &pat)
{
    *firstFree() = new Record 
        {key, pat[1], pat[2], pat[4], pat[5], pat[6], pat[7], pat[8], pat[9]};
}
