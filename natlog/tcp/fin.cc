#include "tcp.ih"

void TCP::fin(Record *record)
{
    auto iter = find(record->key());

    if (iter == end())                    // the local host doesn't FIN
        iter = find(record->dstKey());    // maybe it's the remote host

    if (iter != end())
    {
        log(iter->second);    
        erase(iter);                        // remove the entry
    }

    delete record;
}
