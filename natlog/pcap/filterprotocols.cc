#include "pcap.ih"

void Pcap::filterProtocols()
{
    enum 
    {
        OPTIMIZE = true
    };

    string filterExpr = Options::instance().protocolNames();

    if (pcap_compile(d_pcap, &d_pcapFilter, 
                     filterExpr.c_str(), OPTIMIZE, d_net) == -1) 
        fmsg << "Pcap compilation of `" << filterExpr << 
                            "' failed: " << pcap_geterr(d_pcap) << endl;
    
    if (pcap_setfilter(d_pcap, &d_pcapFilter) == -1) 
         fmsg << "Couldn't install filter `" << 
                filterExpr << ": " << pcap_geterr(d_pcap) << endl;
}
