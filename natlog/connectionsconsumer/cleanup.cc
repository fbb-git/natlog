#include "connectionsconsumer.ih"

void ConnectionsConsumer::cleanup(
            time_t now_ttl, 
            mutex &mapMutex, RecordMap &map,
            void (ConnectionsConsumer::*logFun)(Record const &, char const *),
            char const *type)
{
    vector<size_t> remove;
    lock_guard<mutex> lg(mapMutex);

    for (value_type &value: map)
    {
//if (&map == &d_udp)
//CERR << "key: " << value.second.key() << ", lastused: " << 
//value.second.lastUsed() << ", now_ttl: " << now_ttl << '\n';
            
        if (value.second.lastUsed() < now_ttl)
        {
            (this->*logFun)(value.second, type);
            remove.push_back(value.first);
        }
    }

    for (size_t key: remove)
        map.erase(map.find(key));
}
