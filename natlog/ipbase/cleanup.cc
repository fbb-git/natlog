#include "ipbase.ih"

//f: IPbase::cleanup(long)
    //c: IPbase::cleanupHook()
    //c: TCP::cleanupHook()
    //c: UDP::cleanupHook()

void IPbase::cleanup(time_t now_ttl)
{
    vector<uint64_t> remove;
    lock_guard<mutex> lg(d_mutex);

    for (auto &value: d_map)
    {
        if (value.second->lastUsed() < now_ttl)
        {
            log(*value.second);
            remove.push_back(value.first);
        }
    }

    for (uint64_t key: remove)
        erase(find(key));

    cleanupHook();
}
