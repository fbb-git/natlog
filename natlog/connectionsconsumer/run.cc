#include "connectionsconsumer.ih"

void ConnectionsConsumer::run()
{
    thread cleanupThread;

    if (Options::instance().realTime())
        cleanupThread = thread{ &ConnectionsConsumer::cleanupWrap, this };

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

    if (Options::instance().realTime())
        cleanupThread.join();
    else
        cleanupCompleted(time(0) + 1);

    cleanup(time(0) + 1, d_tcpMutex, d_tcp,
                                    &ConnectionsConsumer::logTCP_UDP, "tcp");
}









