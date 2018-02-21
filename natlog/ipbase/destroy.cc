#include "ipbase.ih"

void IPbase::destroy(Record const *record)
try
{                                       // find this record's accumulated data
    auto iter = find(record->key());

    if (iter == end())                  // unknown record: no existing
        throw false;                    // connection

    auto *accu = iter->second;

    accu->addSentBytes(record);
    accu->addReceivedBytes(record);
    log(accu);

    erase(iter); 
    throw;
}
catch (...)
{
    delete record;
}

