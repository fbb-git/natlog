#include "connectionsconsumer.ih"

void ConnectionsConsumer::run()
{
    thread cleanup{ &ConnectionsConsumer::cleanupWrap, this };

    while (true)
    {
        d_storage.consumeWait();

        if (d_storage.empty())
            break;

        Record &record = d_storage.fetch(); // makes available the next
                                            // record. Since this is the
                                            // only thread fetching records
                                            // there's no need to copy the
                                            // record at this point
        d_storage.produceNotify();
                                            // process the incoming protocol
                                            // data, calls tcp, udp or icmp
        (this->*s_handler[record.protocol()])(record);  
    }

    cleanup.join();
}




