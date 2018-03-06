#include "connectionsconsumer.ih"

void ConnectionsConsumer::signalHandler(size_t signum)
{
    IPbase::setLogType(IPbase::EOP);
}

