#include "devicesproducer.ih"

DevicesProducer::~DevicesProducer()
{
    if (not d_endSignal)
        d_stdMsg << "monitoring " << d_in << 
                    " and " << d_out << " ends" << endl;
}





