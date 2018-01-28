#include "nic.ih"

void NIC::set(Record::Type type, string const &address, string const &mask)
{
    d_nic[type] =                           // found it.
            {
                inet_network(address.c_str()),
                inet_network(mask.c_str())
            };
}
