#ifndef INCLUDED_DEVICES_
#define INCLUDED_DEVICES_

#include "../pcaprecord/pcaprecord.h"

class Options;

namespace FBB
{
    class SyslogStream;
}

class Devices
{
    PcapRecord d_record;
    Options &d_options;
    FBB::SyslogStream &d_syslog;

    public:
        Devices(FBB::SyslogStream &syslog);
        void run();

    private:
};
        
#endif
