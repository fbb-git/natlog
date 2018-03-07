#include "ipbase.ih"

void IPbase::erase(RecordMap::iterator const &iter)
{
    d_map.erase(iter);
}
