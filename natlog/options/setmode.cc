#include "options.ih"

void Options::setMode()
{
    if (d_arg[0] == "conntrack"s)
        d_mode = CONNTRACK;
    else if (d_arg[0] == "tcpdump"s && d_arg.nArgs() >= 3)
        d_mode = TCPDUMP;
    else if (d_arg.nArgs() == 2)
        d_mode = PCAP;
    else
        throw Exception() << "Mode specification error";
}
