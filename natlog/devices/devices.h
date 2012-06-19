#ifndef INCLUDED_DEVICES_
#define INCLUDED_DEVICES_

#include <iosfwd>

#include "../pcaprecord/pcaprecord.h"

class Options;

class Devices
{
    PcapRecord d_record;
    Options &d_options;
    std::ostream &d_out;

    public:
        Devices(std::ostream &out);
        void run(std::ostream &parent);
};
        
#endif
