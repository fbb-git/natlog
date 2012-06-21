#include "pcap.ih"

void Pcap::filter(string const &filterExpr, bool optimize)
{
    if (pcap_compile(d_pcap, &d_pcapFilter, 
                     filterExpr.c_str(), optimize, d_net) == -1) 
        throw Errno(1, "[Fatal] ") << "Pcap compilation of `" << filterExpr << 
                            "' failed: " << pcap_geterr(d_pcap);
    
    if (pcap_setfilter(d_pcap, &d_pcapFilter) == -1) 
         throw Errno(1, "[Fatal] ") << "Couldn't install filter `" << 
                filterExpr << ": " << pcap_geterr(d_pcap);
}
