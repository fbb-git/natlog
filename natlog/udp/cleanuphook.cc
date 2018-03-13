#include "udp.ih"

namespace {
    size_t a_udpSize = 50;
}

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

    maybeSizeLog(&a_udpSize, d_keyMap.size(), "UDP");
}
