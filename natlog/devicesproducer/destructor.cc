#include "devicesproducer.ih"

DevicesProducer::~DevicesProducer()
{
    if (not d_endSignal)
        d_stdMsg << "monitoring " << d_inName << 
                    " and " << d_outName << " ends" << endl;
}





