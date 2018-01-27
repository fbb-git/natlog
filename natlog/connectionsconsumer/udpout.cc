#include "connectionsconsumer.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a known ID packet the via-data can be set
    // and the entry can be removed from d_id, as no information
    // about this connection on the OUT device is used anymore.

extern ofstream info;

void ConnectionsConsumer::udpOut(Record &record)
{
    auto iterID = d_id.find(record.id());

    if (iterID == d_id.end())           // irrelevant UDP packet
        return;                         //  no further actions required.

                                        // find the matching record via 
                                        //  its key
    auto iter = d_udp.find( iterID->second );
    if (iter == d_udp.end())            // not available for some reason
        return;

    auto &accu = iter->second;

    if (accu.sourceIP() != record.sourceIP())
    {
info << "   normal: " << accu.sourceIPstr() << " to " << accu.destIPstr() << 
" via " << record.sourceIPstr() << endl;

        accu.setViaIP(record.sourceIP());
        accu.setViaPort(record.sourcePort());
    }
    else
    {
info << "   reverse: " << accu.sourceIPstr() << " to " << accu.destIPstr() << 
" via " << record.destIPstr() << endl;

        accu.reverse();
        accu.setViaIP(record.destIP());
        accu.setViaPort(record.destPort());

info << "          : " << accu.sourceIPstr() << " to " << accu.destIPstr() << 
" via " << record.destIPstr() << endl;
    }

    d_id.erase(iterID);                 // remove the ID information
}
