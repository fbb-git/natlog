#include "record.ih"

void Record::setVia(uint64_t key)
{
    Key split;
    split.key = key;

    d_viaIP = split.v32;
    d_viaPort = split.v16;
}
