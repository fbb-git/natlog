#include "tcpdumpproducer.ih"

TcpdumpProducer::~TcpdumpProducer()
{
    delete[] d_buffer;
}
