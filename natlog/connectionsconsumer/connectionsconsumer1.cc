#include "connectionsconsumer.ih"

ConnectionsConsumer::ConnectionsConsumer(ostream &stdMsg, Storage &storage)
:
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_ttl(Options::instance().ttl())
{}
