#include "ipbase.ih"

void IPbase::newKey(RecordMap::iterator const &iter, Record const *next)
{
// CERR << "begin\n";
    Record *xfer = iter->second;        // keep the Record
// CERR << "size: " << d_map.size() << ": " << *xfer << '\n';
    d_map.erase(iter);                  // erase the old key entry

// CERR << "erased\n";
                                        // set the via-address and via-port
    xfer->setViaIP(next->sourceIP());
// CERR << "via IP\n";

    xfer->setViaPort(next->sourcePort());

// CERR << "via port\n";

    insert(xfer->srcKey(), xfer);       // store the record with the new key

// CERR << "end\n";
}
