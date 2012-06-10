#include "main.ih"

int main(int argc, char **argv)
try
{
    if (argc == 1)
    {
        usage(argv[0]);
        return 1;
    }

    Pcap pcap(argv[1]);

    string filterExpr;
    for (char **arg = argv + 2; *arg; ++arg)
    {
        filterExpr += *arg;
        filterExpr += ' ';
    }

    pcap.filter(filterExpr);

}
catch (...)
{
    return 1;
}
