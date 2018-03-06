#include "natfork.ih"

//f: NatFork::childProcess()
    //c: DevicesProducer::DevicesProducer(std::ostream&, Storage&)
    //c: TcpdumpProducer::TcpdumpProducer(std::ostream&, Storage&)
    //c: ConntrackProducer::ConntrackProducer(std::ostream&, Storage&)

void NatFork::childProcess()
{
    ShowSeconds::setFormat();

    Storage storage;

    // Constructing of the producers may fail. At that point messages can
    // still be written to cout since we're busy starting the daemon.
    // Once the producers have been constructed, messages to cout are
    // suppressed by prepareDaemon below

    unique_ptr<Producer> producer { 
                            (*s_producer[d_mode]) (d_stdMsg, storage) 
                         };
    ConnectionsConsumer connections{ d_stdMsg, storage };

    d_stdMsg << "processing: " << d_options.protocolNames() << endl;

    if (d_options.daemon())
        prepareDaemon();

    RotatingStreambuf::startThread();

    thread producerThread{ Producer::process, producer.get(), ref(storage) };

    connections.run();

    producerThread.join();

    d_stdMsg << "NatFork::childProcess notifying RotatingStreambuf" << endl;    

    RotatingStreambuf::notify();             // ends the log-rotating threads.

    d_stdMsg << "NatFork::childProcess ends" << endl;    
}







