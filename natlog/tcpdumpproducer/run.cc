#include "tcpdumpproducer.ih"

void TcpdumpProducer::run()
{
    Exception::open(d_in.stream, d_inName); // throw exceptions on failure
    Exception::open(d_out.stream, d_outName);

    d_in.stream.ignore(24);            // skip the global header, see
    d_out.stream.ignore(24);            // pcapfile.txt

    d_stdMsg << "starting reading packets from " << d_inName << 
                              " and " << d_outName << endl;
    
    get(d_in);                         // fetch the first packets from
    get(d_out);                         // both files. 

    process();                          // process all packets.
}
