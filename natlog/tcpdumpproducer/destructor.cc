#include "tcpdumpproducer.ih"

TcpdumpProducer::~TcpdumpProducer()
{
    delete[] d_buffer;

    d_stdMsg << "processed all packets from " << d_inName << 
                " and " << d_outName << endl;
}
