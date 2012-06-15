#include "pcaprecord.ih"

void PcapRecord::store(Record *record)
{
    time_t now = time(0);
    size_t idx = 0;

    for (auto &element: d_connections)
    {
        if (element == 0)               // empty element
        {
            element = record;           // store the record in the empty spot
            return;
        }
                                        // delete old, incomplete records
        if (element->status == INCOMPLETE && seconds(*element) + TTL < now)
        {
            imsg << "Replacing incomplete #" << idx << endl;
            delete element;
            element = record;
            return;
        }
        ++idx;
    }
    d_connections.push_back(record);    // add the record at the end
    imsg << "New index #" << (d_connections.size() - 1) << endl;
}




