#include "natfork.ih"

Producer *(*NatFork::s_producer[]) (ostream &stdMsg, Storage &storage) = 
{
    Producer::alloc<ConntrackProducer>,     // must match the Options::Mode
    Producer::alloc<DevicesProducer>,       //  enum entries
    Producer::alloc<TcpdumpProducer>
};

