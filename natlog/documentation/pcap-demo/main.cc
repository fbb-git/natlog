#include "main.ih"

int main(int argc, char **argv)
try
{
    if (argc == 1)
    {
        usage(argv[0]);
        return 1;
    }

    Pcap pcap(argv[1], true, PcapPacket::SIZEOF_TCP_HEADER);

    string filterExpr;
    for (char **arg = argv + 2; *arg; ++arg)
    {
        filterExpr += *arg;
        filterExpr += ' ';
    }
    filterExpr.resize(filterExpr.length() - 1);

    pcap.filter(filterExpr);

    if (emsg.count() != 0)
        return 1;

    pcap.loop();

}
catch (...)
{
    return 1;
}
