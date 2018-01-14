#include "tcpdumpproducer.ih"

void TcpdumpProducer::store(Record::Type type, Data &data)
{
    if (data.hdr.len > d_bufLen)      // ip header length already in host byte
    {                               // order
        delete[] d_buffer;
        d_buffer = new char[ d_bufLen = data.hdr.len ];
    }

    if (not data.stream.read(d_buffer, data.hdr.len))
        throw Exception{} << ": corrupted tcpdump file `" << 
                    (type == Record::IN ? d_inName : d_outName) << '\'';

    u_char const *buffer = reinterpret_cast<u_char const *>(d_buffer);

    if (d_options.hasProtocol(
            IP_Types::get<IP_Types::IP_Header>(buffer).protocol)
    )
        d_storage.push( TcpdumpRecord{ type, data.hdr, buffer } );

    get(data);
}




