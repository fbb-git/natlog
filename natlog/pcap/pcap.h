#ifndef INCLUDED_PCAP_
#define INCLUDED_PCAP_

#include <iosfwd>
#include <pcap.h>

class Pcap
{
    pcap_t *d_pcap;
    struct bpf_program d_pcapFilter;    
    bpf_u_int32 d_net;
    int d_shift;

    public:
        Pcap(char const *device, bool promisc = false, size_t snapLen = 1500, 
             size_t timeOutMs = 1000);

        void loop(void *pcapFilterPtr, pcap_handler callback);
        void stop();

        int shiftPacketBegin() const;

    private:
        void filterProtocols();                 // filter interesting prot's.
        void computeShift(char const *device);  // from Pcap(): sets d_shift
};

inline void Pcap::stop()
{
    pcap_breakloop(d_pcap);
}

inline int Pcap::shiftPacketBegin() const
{
    return d_shift;
}

#endif





