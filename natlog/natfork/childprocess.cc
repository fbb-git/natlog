#include "natfork.ih"

void NatFork::childProcess()
{
    ShowSeconds::setFormat();

    Storage storage;

    // Constructing of the producers may fail. At that point messages can
    // still be written to cout since we're busy starting the daemon.
    // Once the producers have been constructed, messages to cout are
    // suppressed by prepareDaemon below

    unique_ptr<Producer> producer {
        d_mode == Options::CONNTRACK ? 
            Producer::alloc<ConntrackProducer>(d_stdMsg, ref(storage)) : 
        d_mode == Options::PCAP ? 
            Producer::alloc<DevicesProducer>(d_stdMsg, ref(storage))   :
        // TCPDUMP:
            Producer::alloc<TcpdumpProducer>(d_stdMsg, ref(storage))
    };

    ConnectionsConsumer connections{ d_stdMsg, storage };

    if (d_options.daemon())
        prepareDaemon();

    thread{ Producer::process, producer.get() }.detach();

    connections.run();              // this must end before...
}







