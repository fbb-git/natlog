#include "connectionsconsumer.ih"

inline void ConnectionsConsumer::signalHandler(size_t signum)
{
    IPbase::setLogType(IPbase::EOP);
}

