#ifndef INCLUDED_PCAPFILTER_
#define INCLUDED_PCAPFILTER_

#include <string>
#include <mutex>

#include <vector>

#include <bobcat/signal>

#include "../pcap/pcap.h"
#include "../pcaprecord/pcaprecord.h"

struct PcapFilter: public FBB::SignalHandler
{
    typedef PcapRecord::Type Type;

    private:
        std::string d_device;
        PcapRecord &d_record;
        Type d_type;
        Pcap d_pcap;

        static std::mutex s_recordMutex;

        std::vector<PcapRecord *> d_connections;

    public:
        PcapFilter(char const *device, PcapRecord &record, Type type);
        void operator()();
        
    private:
        void inDevice(PcapPacket const &packet);        // device before NAT
        void outDevice(PcapPacket const &packet);       // device after NAT

        void saveAdd(PcapPacket const &packet);
        void saveRemove(PcapPacket const &packet);


        static void callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                             u_char const *bytes);
        int shiftPacketBegin() const;

        void signalHandler(size_t signum) override;
};

#endif





