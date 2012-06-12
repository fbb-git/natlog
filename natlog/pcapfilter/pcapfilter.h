#ifndef INCLUDED_PCAPFILTER_
#define INCLUDED_PCAPFILTER_

#include <string>
#include <mutex>

#include "../signal/signal.h"

#include "../pcap/pcap.h"
#include "../pcaprecord/pcaprecord.h"

struct PcapFilter: public SignalHandler
{
    enum Type
    {
        IN,
        OUT
    };

    private:
        std::string d_device;
        PcapRecord &d_record;
        Type d_type;
        Pcap d_pcap;

        static char s_filterExpr[];
        static std::mutex s_recordMutex;

    public:
        PcapFilter(char const *device, PcapRecord &record, Type type);
        void operator()();
        void stop();
        
    private:
        void inDevice(PcapPacket const &packet);
        void outDevice(PcapPacket const &packet);

        void saveAdd(PcapPacket const &packet);

        static void callback(PcapFilter *pf, struct pcap_pkthdr const *hdr,
                             u_char const *bytes);

        virtual void signaled(size_t signum) override;
};

#endif





