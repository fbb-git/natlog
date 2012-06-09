#ifndef INCLUDED_PCAP_
#define INCLUDED_PCAP_

#include <memory>

#include <pcap/pcap.h>

class Pcap
{
    std::unique_ptr<char> d_errBuf;
    pcap_t *d_pcap;

    public:
        Pcap(char const *device, bool promisc = false, size_t snapLen = 1500, 
             size_t timeOutMs = 1000);

    private:
};
        
#endif
