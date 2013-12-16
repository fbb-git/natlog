#include "conntrackrecord.ih"

void ConntrackRecord::addTcpudp(std::string const &key, Pattern const &pat)
{
    *firstFree() = new Record 
                    {
                        key, 
                        pat[1], pat[2], pat[4], 
                        pat[5], pat[6], pat[7], pat[8], 
                        pat[9], pat[10]
                    };
}
