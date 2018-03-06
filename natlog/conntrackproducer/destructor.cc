#include "conntrackproducer.ih"

//f: ConntrackProducer::~ConntrackProducer()
    //c: ConntrackProducer::signalHandler(unsigned long)

ConntrackProducer::~ConntrackProducer()
{
    d_stdMsg << "monitoring conntrack ends" << endl;
}
