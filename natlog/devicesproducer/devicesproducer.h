#ifndef INCLUDED_DEVICESPRODUCER_
#define INCLUDED_DEVICESPRODUCER_

#include <iosfwd>

#include "../producer/producer.h"

class Options;
class Storage;

class DevicesProducer: public Producer
{
    Options &d_options;
    std::ostream &d_stdMsg;
    Storage &d_storage;

    public:
        DevicesProducer(std::ostream &stdMsg, Storage &storage);
        ~DevicesProducer() override;

    private:
        void run() override;
};
        
#endif
