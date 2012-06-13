#ifndef INCLUDED_PCAP_
#define INCLUDED_PCAP_

#include <iosfwd>
#include <pcap/pcap.h>
#include <fstream>

class Pcap
{
    pcap_t *d_pcap;
    struct bpf_program d_pcapFilter;    
    bpf_u_int32 d_IP;           // The IP address of our sniffing device

    static std::ofstream s_out;

    public:
        Pcap(char const *device, bool promisc = false, size_t snapLen = 1500, 
             size_t timeOutMs = 1000);

        bool filter(std::string const &filterExpr, bool optimize = true);
        void loop();
        
    private:
        static void callback(u_char *user, struct pcap_pkthdr const *hdr,
                             const u_char *bytes);
};
        
#endif
