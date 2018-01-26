#include "record.ih"

char const *Record::protocolStr() const
{
    switch (d_protocol)
    {
        case ICMP:
        return "icmp";

        case UDP:
        return " udp";

        case TCP:
        return " tcp";
    }
}
