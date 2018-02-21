#include "connectionsconsumer.ih"

void ConnectionsConsumer::newKey(RecordMap &map, 
                                 RecordMap::iterator const &iter,
                                 Record const *record)
{
//CERR << "CURRENT: " << *iter->second << "\n"
//        "VIA:     " << *record << endl;

    Record *xfer = iter->second;        // keep the Record
    map.erase(iter);                    // erase the old key entry

                                        // set the via-address and via-port
    xfer->setViaIP(record->sourceIP());
    xfer->setViaPort(record->sourcePort());

                                        // store the record with the new key
    map.insert( value_type{ xfer->srcKey(), xfer } );

//CERR << "SETTING VIA: NEW KEY: " << xfer->srcKey() << '\n';


}
