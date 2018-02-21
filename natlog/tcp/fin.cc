#include "tcp.ih"

void TCP::fin(Record *record)
{
//CERR << "begin\n";
    auto iter = find(record->srcKey());

    if (iter == end())                    // the local host doesn't FIN
        iter = find(record->dstKey());    // maybe it's the remote host

    if (iter != end())
    {
        log(iter->second);    
        erase(iter);                        // remove the entry
    }

    delete record;
//CERR << "end\n";
}
