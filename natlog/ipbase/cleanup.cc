#include "ipbase.ih"

void IPbase::cleanup(time_t now_ttl)
{
    vector<uint64_t> remove;
    lock_guard<mutex> lg(d_mutex);

    for (value_type &value: d_map)
    {
        if (value.second->lastUsed() < now_ttl)
        {
            log(value.second);
            remove.push_back(value.first);
        }
    }

    for (size_t key: remove)
        erase(find(key));
}
