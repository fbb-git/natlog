#include "ipbase.ih"

void IPbase::viaAndSrcKey(RecordMap::iterator const &iter, Record const *next)
{
    Record *xfer = iter->second;        // keep the Record

    d_map.erase(iter);                  // erase the old key entry

    xfer->setViaIP(next->sourceIP());   // set the via-address and via-port
    xfer->setViaPort(next->sourcePort());

CERR << "PRE key: " << xfer->key() << '\n';

    xfer->setSrcKey();

CERR << "POST key: " << xfer->key() << '\n';

    insert(xfer);                       // store the record with the new key
}
