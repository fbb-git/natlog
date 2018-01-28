#ifndef INCLUDED_NIC_
#define INCLUDED_NIC_

#include <iosfwd>
#include "../record/record.h"

class NIC
{
    struct Addresses
    {
        size_t address = 0;
        size_t mask = 0;
    };

    Addresses d_nic[Record::nTypes];    // modify when Record::Type is
                                        // modified

    public:
        void set(Record::Type, std::string const &name);
        void set(Record::Type, std::string const &address,
                               std::string const &mask);

                
        size_t address(Record::Type) const;
        bool mask(Record::Type, size_t address) const;
        
    private:
};
        
inline size_t NIC::address(Record::Type type) const
{
     return d_nic[type].address;
}

inline bool NIC::mask(Record::Type type, size_t address) const
{
    return (d_nic[type].address & d_nic[type].mask)
            == 
            (address            & d_nic[type].mask);

}

extern NIC g_nic;

#endif
