#include "udp.ih"

namespace {
    size_t a_udpSize = 50;
    size_t a_recordCount = 50;
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

    if (not g_debug.good())
        return;

    bool newSize =  size() > a_udpSize;
    if (newSize)
        a_udpSize = size() + 50;

    bool newCount = Record::count() > a_recordCount;
    if (newCount)
        a_recordCount = Record::count() + 50;

    if (newCount or newSize)
        g_debug << "UDP size: " << size() << 
                    ", keyMap size: " << d_keyMap.size() <<
                    ", #records: " << Record::count() << endl;
}
