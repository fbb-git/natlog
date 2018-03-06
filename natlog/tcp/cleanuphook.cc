#include "tcp.ih"

void TCP::cleanupHook()
{
    vector<size_t> remove;

    for (auto &value: d_keyMap)
    {
        if (find(value.second) == end())
            remove.push_back(value.first);
    }

    for (size_t key: remove)
        d_keyMap.erase(d_keyMap.find(key));

    if (g_debug.good() and size() % 100 == 0)
        g_debug << "TCP size: " << size() << 
                    ", keyMap size: " << d_keyMap.size() <<
                    ", #records: " << Record::count() << '\n';
}
