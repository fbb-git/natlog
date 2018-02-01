#include "conntrackproducer.ih"

void ConntrackProducer::process(string const &line)
{
    imsg << "LINE: " << line << endl;

    if (s_tcpudp << line)               // try to match UDP or TCP
    {
        if ( d_options.hasProtocol( 
                        s_tcpudp[ static_cast<size_t>(CTtcpudp::PROTOCOL) ] ) 
        )
            d_storage.push( ConntrackRecord{ Record::TCP,   // (also for UDP)
                                             s_tcpudp } );
        return;
    }

                                        // or try to match ICMP
    if (s_icmp << line and d_options.hasProtocol(Record::ICMP))
    {
        d_storage.push( ConntrackRecord{ Record::ICMP, s_icmp } );
        return;
    }

    imsg << "   (not matched)" << endl;
}

