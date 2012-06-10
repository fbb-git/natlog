#include "pcap.ih"

bool Pcap::filter(string const &filterExpr, bool optimize)
{
    if (pcap_compile(d_pcap, &d_pcapFilter, 
                     filterExpr.c_str(), optimize, d_IP) == -1) 
    {
        emsg << "Pcap compilation of `" << filterExpr << "' failed: " <<
                pcap_geterr(d_pcap) << endl;
        return false;
    }
    
	if (pcap_setfilter(d_pcap, &d_pcapFilter) == -1) 
    {
		 emsg << "Couldn't install filter `" << filterExpr << ": " <<
                 pcap_geterr(d_pcap) << endl;
		 return false;
	 }

    return true;
}
