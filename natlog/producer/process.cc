#include "producer.ih"

//f: Producer::process(Producer*, Storage&)
    //c: DevicesProducer::run()
    //c: ConntrackProducer::run()
    //c: TcpdumpProducer::run()

void Producer::process(Producer *producer, Storage &storage)
{
    producer->run();
    storage.setEmpty();
}

