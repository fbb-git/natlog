#include "producer.ih"

void Producer::process(Producer *producer, Storage &storage)
{
    producer->run();
    storage.setEmpty();
}

