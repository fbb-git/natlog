#include "connectionsconsumer.ih"

void ConnectionsConsumer::cleanup(
            time_t now_ttl, 
            mutex &mapMutex, RecordMap &map,
            void (ConnectionsConsumer::*logFun)(Record const *, char const *),
            char const *type)
{
    vector<size_t> remove;
    lock_guard<mutex> lg(mapMutex);

    for (value_type &value: map)
    {
        if (value.second->lastUsed() < now_ttl)
        {
            (this->*logFun)(value.second, type);
            remove.push_back(value.first);
        }
    }

    for (size_t key: remove)
        erase(map, map.find(key));
}
