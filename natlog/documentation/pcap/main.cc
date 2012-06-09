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

}
catch (...)
{
    return 1;
}
