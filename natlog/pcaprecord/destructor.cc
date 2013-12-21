#include "pcaprecord.ih"

PcapRecord::~PcapRecord()
{
    size_t endSeconds = time(0);

    d_stdMsg << "monitoring devices through pcap ends" << endl;

    for (auto &rec: d_connections)
    {
        if (rec && rec->status == ESTABLISHED)
            log(rec, endSeconds, 0);
    }
    
}
