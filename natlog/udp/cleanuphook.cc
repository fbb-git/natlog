#include "udp.ih"

void UDP::cleanupHook()
{
    vector<size_t> remove;

    for (auto &value: d_keyMap)
    {
        if (find(value.second) == end())
            remove.push_back(value.first);
    }

    for (size_t key: remove)
        d_keyMap.erase(d_keyMap.find(key));
}
