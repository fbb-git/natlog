#include "nic.ih"

void NIC::set(Record::Type type, string const &address, string const &maskStr)
{
    uint32_t mask = 
        maskStr[0] == '/' ?
            ~((1 << stoul(maskStr.substr(1))) - 1)
        :
            inet_network(maskStr.c_str());

    d_nic[type] =                           // found it.
            {
                ntohl(inet_network(address.c_str())),
                ntohl(mask)
            };
}
