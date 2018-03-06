#include "ipbase.ih"

//f: IPbase::log(Record const*) const
    //c: IPbase::logConnection(Record const*) const
    //c: ICMP::logConnection(Record const*) const

void IPbase::log(Record const *record) const
{
    logConnection(record);
}
