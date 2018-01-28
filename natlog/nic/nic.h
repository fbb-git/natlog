#ifndef INCLUDED_NIC_
#define INCLUDED_NIC_

#include <unordered_map>
#include <iosfwd>

class NIC
{
    struct Addresses
    {
        uint32_t address = 0;
        uint32_t mask = 0;
    };

    std::unordered_map<std::string, Addresses> d_map;
        
    public:
        void set(std::string const &name);

        uint32_t address(std::string const &name);
        uint32_t mask(std::string const &name);
        
    private:
};
        
inline uint32_t NIC::address(std::string const &name)
{
    return d_map[name].address;
}

inline uint32_t NIC::mask(std::string const &name)
{
    return d_map[name].mask;
}

extern NIC g_nic;

#endif
