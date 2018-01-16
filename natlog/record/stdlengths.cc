#include "record.ih"

Record::Lengths Record::stdLengths(u_char const *packet) const
{
                                            // hdrLength itself selects its
                                            // bits
    return 
    {
        size_t(get<IP_Header>(packet).hdrLength << 2),
        ntohs(get<IP_Header>(packet).length),

            // 4 most significant bits: # 32 bit words
            // so: shr 4 to het the # 32 bit words, and 
            // << 2 to multiply by 4 to get the #bytes before the data
        size_t(get<TCP_Header>(packet).dataOffset >> 4 << 2),
    };
}


