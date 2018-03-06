#include "devicesproducer.ih"

//f: DevicesProducer::~DevicesProducer()
    //c: DevicesProducer::signalHandler(unsigned long)
DevicesProducer::~DevicesProducer()
{
    if (not d_endSignal)
        d_stdMsg << "monitoring " << d_inName << 
                    " and " << d_outName << " ends" << endl;
}





