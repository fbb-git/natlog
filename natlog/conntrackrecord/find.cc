#include "conntrackrecord.ih"

size_t ConntrackRecord::find(std::string const &key) const
{
    for (auto &record: d_connections)
    {
        if (record && record->key == key)
            return &record - &d_connections[0];
    }
    return numeric_limits<size_t>::max();
}
