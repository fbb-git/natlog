#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpIn(Record *record)
{
//CERR << '\n';

    if (g_nic.mask(Record::IN, record->sourceIP())) // package is sent
        icmpOutbound(record);
                                                    // package is received
    else if (g_nic.mask(Record::IN, record->destIP())) 
        icmpInbound(record);
}

