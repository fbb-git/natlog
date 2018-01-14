#include "tcpdumpproducer.ih"

bool TcpdumpProducer::Data::before(Data const &other)
{
    return 
        hdr.seconds < other.hdr.seconds 
        ||
        (
            hdr.seconds == other.hdr.seconds 
            &&
            hdr.muSeconds < other.hdr.muSeconds
        ); 
}
