#include "connectionsconsumer.ih"

void ConnectionsConsumer::signalHandler([[maybe_unused]] size_t signum)
{
    IPbase::setLogType(IPbase::EOP);
}

