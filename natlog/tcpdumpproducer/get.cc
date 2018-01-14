#include "tcpdumpproducer.ih"

// static
void TcpdumpProducer::get(Data &data)
{
//    if (data.stream.good())    
//        cerr << __FILE__ ": packet at: " << hex << data.stream.tellg() <<
//            ", length at: " << (unsigned long long)data.stream.tellg() + 8;

    data.stream.read(reinterpret_cast<char *>(&data.hdr), 
                    sizeof(TcpdumpRecord::PktHdr));
    
    if (not data.stream.good())
        data.hdr.seconds = numeric_limits<uint32_t>::max();

//    else
//       cerr <<  ", length: " << data.hdr.len << 
//            ", next packet should be at: " << 
//            (unsigned long long)data.stream.tellg() + data.hdr.len << '\n';

}
