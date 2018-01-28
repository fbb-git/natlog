#include "nic.ih"

bool NIC::mask(Record::Type type, size_t address) const
{
    CERR << hex << d_nic[type].address << ' ' << d_nic[type].mask << ' ' <<
            address  << ' ' << d_nic[type].mask << '\n';

    return (d_nic[type].address & d_nic[type].mask)
            == 
            (address            & d_nic[type].mask);

}
