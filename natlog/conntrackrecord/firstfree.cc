#include "conntrackrecord.ih"

ConntrackRecord::Record **ConntrackRecord::firstFree()
{
    for (auto &record: d_connections)
    {
        if (record == 0)
        {
            imsg << "At #" << (&record - &d_connections[0]) << endl;
            return &record;
        }
    }

    d_connections.push_back(0);
    imsg << "New index #" << (d_connections.size() - 1) << endl;
    return &d_connections.back();
}

