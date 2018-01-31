#include "options.ih"

void Options::setMode()
{
    if (d_arg[0] == "conntrack"s)
        d_mode = CONNTRACK;
    else if (d_arg.nArgs() == 2)
        d_mode = PCAP;
    else if (d_arg.nArgs() == 6)
        d_mode = TCPDUMP;
    else
        throw Exception() << "Mode specification error";
}
