#include "connectionsconsumer.ih"

//static size_t count = 0;

void ConnectionsConsumer::run()
{
    thread cleanupThread;

        // when logging in Conntrack-mode or Device-mode (realTime)
        // inspect the TTL of the incoming packages in the background.
    if (d_options.realTime())
        cleanupThread = thread{ &ConnectionsConsumer::cleanupWrap, this };

    while (true)
    {
        d_storage.consumeWait();

        if (d_storage.empty())
            break;

        Record *record = d_storage.fetch(); // makes available the next
                                            // record-> Since this is the
                                            // only thread fetching records
                                            // there's no need to copy the
                                            // record at this point
        d_storage.produceNotify();

//        if (d_options.debug())
//        {
//            if (count++ % 100 == 0)
//                g_debug << count << ": " << *record << endl;
//        }
                                            // process the incoming protocol
                                            // data, calls tcp, udp or icmp
        d_handler[record->protocol()]->process(record);  
    }

    if (d_options.realTime())
        cleanupThread.join();
        
    time_t eop = time(0) + 1;

    cleanupICMP_UDP(eop);                   // what's still in the maps is
                                            // there at EOP
    d_tcp.cleanup(eop);
}









