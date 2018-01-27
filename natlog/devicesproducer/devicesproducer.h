#ifndef INCLUDED_DEVICESPRODUCER_
#define INCLUDED_DEVICESPRODUCER_

#include <iosfwd>

#include <bobcat/signal>
#include <bobcat/semaphore>

#include "../producer/producer.h"

class Options;
class Storage;

class DevicesProducer: public Producer, public FBB::SignalHandler
{
    Options &d_options;
    std::ostream &d_stdMsg;
    Storage &d_storage;
    FBB::Semaphore d_signaled;
    bool d_endSignal = false;

    public:
        DevicesProducer(std::ostream &stdMsg, Storage &storage);
        ~DevicesProducer() override;

    private:
        void run() override;
        void signalHandler(size_t signum) override;

        void handleSignals();
};
        
#endif
