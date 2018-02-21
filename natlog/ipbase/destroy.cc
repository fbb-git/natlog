#include "ipbase.ih"

    // used for TCP/UDP
void IPbase::destroy(Record const *record)
{
                                        // find this record's accumulated data
    auto iter = d_map.find(record->srcKey());

    if (iter == d_map.end())            // unknown record: no existing
        return;                         // connection

    auto *accu = iter->second;

    accu->addSentBytes(record);
    accu->addReceivedBytes(record);

    log(iter->second);

    delete record;
    erase(iter); 
}

