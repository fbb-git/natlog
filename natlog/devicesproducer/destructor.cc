#include "devicesproducer.ih"

DevicesProducer::~DevicesProducer()
{
    if (not d_endSignal)
        d_stdMsg << "monitoring " << d_options[0] << 
                    " and " << d_options[1] << " ends" << endl;
}





