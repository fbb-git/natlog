#include "ipbase.ih"

void IPbase::setVia(RecordMap::iterator const &iter, Record const &next)
{
    RecordPtr xfer = move(iter->second); // keep the Record

    d_map.erase(iter);                  // erase the old key entry

    xfer->setViaIP(next.sourceIP());    // set the via-address and via-port
    xfer->setViaPort(next.sourcePort());

    insert(xfer);                       // store the record with the new key
}
