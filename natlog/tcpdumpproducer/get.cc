#include "tcpdumpproducer.ih"

// static
void TcpdumpProducer::get(Data &data)
{
    data.stream.read(reinterpret_cast<char *>(&data.hdr), 
                    sizeof(TcpdumpRecord::PktHdr));
    
    if (not data.stream.good())
        data.hdr.seconds = numeric_limits<uint32_t>::max();
}
