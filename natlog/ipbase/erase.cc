#include "ipbase.ih"

void IPbase::erase(RecordMap::iterator const &iter)
{
    delete iter->second;
    d_map.erase(iter);
}
