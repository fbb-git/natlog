#ifndef INCLUDED_PCAPFILTER_
#define INCLUDED_PCAPFILTER_

#include <string>
#include <mutex>

#include <vector>

#include "../pcap/pcap.h"
#include "../pcaprecord/pcaprecord.h"

class Storage;
class Options;

class PcapFilter
{
    Options const &d_options;
    std::ostream &d_stdMsg;
    Storage &d_storage; 

    Record::Type d_type;
    Pcap d_pcap;
    bool d_stop = false;

    public:
        PcapFilter(char const *device, Record::Type, 
                   std::ostream &stdMsg, Storage &storage);
        void operator()();

        void stop();
        
    private:
        static void callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                             u_char const *bytes);

        int shiftPacketBegin() const;
};

#endif





