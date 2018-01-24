#include "pcapfilter.ih"

void PcapFilter::handleSignals()
{
    Signal::instance().add(SIGHUP, *this);
    Signal::instance().add(SIGINT, *this);
    Signal::instance().add(SIGTERM, *this);

}
