#include "devicesproducer.ih"

void DevicesProducer::handleSignals()
{
    Signal::instance().add(SIGHUP, *this);
    Signal::instance().add(SIGINT, *this);
    Signal::instance().add(SIGTERM, *this);
}
