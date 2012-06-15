#include "conntrackrecord.ih"

ConntrackRecord::~ConntrackRecord()
{
    for (auto &record: d_connections)
        delete record;
}

