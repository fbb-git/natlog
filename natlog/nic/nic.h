#ifndef INCLUDED_NIC_
#define INCLUDED_NIC_

#include <iosfwd>
#include "../record/record.h"

class NIC
{
    struct Addresses
    {
        uint32_t address = 0;
        uint32_t mask = 0;
    };

    Addresses d_nic[Record::nTypes];    // modify when Record::Type is
                                        // modified

    public:
        void set(Record::Type, std::string const &name);
        void set(Record::Type, std::string const &address,
                               std::string const &mask);

        
//        uint32_t address(Record::Type);
//        uint32_t mask(Record::Type);
        
    private:
};
        
// inline uint32_t NIC::address(std::string const &name)
// {
//     return d_map[name].address;
// }
// 
// inline uint32_t NIC::mask(std::string const &name)
// {
//     return d_map[name].mask;
// }

extern NIC g_nic;

#endif
