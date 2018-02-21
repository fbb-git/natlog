#include "connectionsconsumer.ih"

void ConnectionsConsumer::erase(RecordMap &map, 
                                RecordMap::iterator const &iter)
{
    delete iter->second;
    map.erase(iter);
}
