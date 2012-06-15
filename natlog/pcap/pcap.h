#ifndef INCLUDED_PCAP_
#define INCLUDED_PCAP_

#include <iosfwd>
#include <pcap/pcap.h>

class Pcap
{
    pcap_t *d_pcap;
    struct bpf_program d_pcapFilter;    
    bpf_u_int32 d_net;
    int d_shift;

    public:
        Pcap(char const *device, bool promisc = false, size_t snapLen = 1500, 
             size_t timeOutMs = 1000);

        bool filter(std::string const &filterExpr, bool optimize = true);
        void loop(u_char *user, pcap_handler callback);
        void stop();

        int shift() const;

    private:
        void computeShift(char const *device);  // from Pcap(): sets d_shift
};

inline void Pcap::stop()
{
    pcap_breakloop(d_pcap);
}

inline int Pcap::shift() const
{
    return d_shift;
}

#endif





