#include "pcaprecord.ih"

PcapRecord::~PcapRecord()
{
    size_t endSeconds = time(0);

    d_syslog << "terminating" << endl;

    for (auto &rec: d_connections)
    {
        if (rec && rec->status == ESTABLISHED)
            log(rec, endSeconds, 0);
    }
    
}
