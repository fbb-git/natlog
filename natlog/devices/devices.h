#ifndef INCLUDED_DEVICES_
#define INCLUDED_DEVICES_

#include <iosfwd>

#include "../pcaprecord/pcaprecord.h"

class Options;

class Devices
{
    PcapRecord d_record;
    Options &d_options;
    std::ostream &d_stdMsg;

    public:
        Devices(std::ostream &stdMsg);
        void run();
};
        
#endif
