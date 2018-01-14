#include "natfork.ih"

void NatFork::childProcess()
{
    ShowSeconds::setFormat();

    if (d_options.daemon())
        prepareDaemon();

    try
    {
        Storage storage;

        unique_ptr<Producer> producer {
            d_mode == Options::CONNTRACK ? 
                Producer::alloc<ConntrackProducer>(d_stdMsg, ref(storage)) : 
            d_mode == Options::PCAP ? 
                Producer::alloc<DevicesProducer>(d_stdMsg, ref(storage))   :
            // TCPDUMP:
                Producer::alloc<TcpdumpProducer>(d_stdMsg, ref(storage))
        };

        ConnectionsConsumer connections{ d_stdMsg, storage };

        thread produce{ Producer::process, producer.get() };

        connections.run();

        produce.join();
    }
    catch (exception const &err)        // Producer errors
    {
        if (not d_options.daemon())
            throw;                      // rethrow the exception

        d_stdMsg << err.what() << endl;
    }

    cleanupPidFile();
        // the ending child process cleans up its own pid file:

    throw Options::OK;              // ends the program or the child process
}







