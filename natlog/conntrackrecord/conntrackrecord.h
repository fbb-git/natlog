#ifndef INCLUDED_CONNTRACKRECORD_
#define INCLUDED_CONNTRACKRECORD_

#include <vector>
#include <string>

namespace FBB
{
    class Pattern;
}

struct ConntrackRecord
{
    struct Record
    {
        std::string key;

        std::string seconds;
        std::string musecs;
        std::string protocol;
        std::string sourceIP;
        std::string destIP;
        std::string sourcePort;
        std::string destPort;
        std::string viaIP;
        std::string viaPort;
    };

    private:
        std::vector<Record *> d_connections;
            
    public:
        ~ConntrackRecord();

        size_t find(std::string const &key) const;
        void addTcpudp(std::string const &key, FBB::Pattern const &pat);
        void addIcmp(std::string const &key, FBB::Pattern const &pat);
        void erase(size_t idx);
        Record const *operator[](size_t idx);
        size_t size() const;

        std::vector<Record *>::const_iterator begin() const;
        std::vector<Record *>::const_iterator end() const;

    private:
        Record **firstFree();

};

inline size_t ConntrackRecord::size() const
{
    return d_connections.size();
}

inline ConntrackRecord::Record const *ConntrackRecord::operator[](size_t idx)
{
    return d_connections[idx];
}

inline std::vector<ConntrackRecord::Record *>::const_iterator 
                                            ConntrackRecord::begin() const
{
    return d_connections.begin();
}

inline std::vector<ConntrackRecord::Record *>::const_iterator 
                                            ConntrackRecord::end() const
{
    return d_connections.end();
}

#endif




