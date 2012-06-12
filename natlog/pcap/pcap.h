#ifndef INCLUDED_PCAP_
#define INCLUDED_PCAP_

#include <iosfwd>
#include <pcap/pcap.h>

class Pcap
{
    pcap_t *d_pcap;
    struct bpf_program d_pcapFilter;    
    bpf_u_int32 d_IP;           // The IP address of our sniffing device

    public:
        Pcap(char const *device, bool promisc = false, size_t snapLen = 1500, 
             size_t timeOutMs = 1000);

        bool filter(std::string const &filterExpr, bool optimize = true);
        void loop(u_char *user, pcap_handler callback);
        void stop();
};
        
inline void Pcap::stop()
{
    pcap_breakloop(d_pcap);
}

#endif
