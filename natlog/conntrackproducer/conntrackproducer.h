#ifndef INCLUDED_CONNTRACKPRODUCER_
#define INCLUDED_CONNTRACKPRODUCER_

#include <iosfwd>

#include <bobcat/pattern>
#include <bobcat/signal>
#include <bobcat/fork>
#include <bobcat/pipe>

#include "../producer/producer.h"

class Options;
class Storage;

namespace FBB
{
    class Pattern;
}

class ConntrackProducer: public Producer, public FBB::Fork, 
                         public FBB::SignalHandler
{
    FBB::Pipe d_pipe;
    Options &d_options;
    std::ostream &d_stdMsg;
    Storage &d_storage;

    bool d_signaled = false;

    static FBB::Pattern s_tcpudp;
    static FBB::Pattern s_icmp;

    public:
        ConntrackProducer(std::ostream &stdMsg, Storage &storage);
        ~ConntrackProducer();

    private:
        void run() override;

        void process(std::string const &line);

        void signalHandler(size_t signum) override;

        void parentProcess() override;
        void childProcess() override;
        void childRedirections() override;
        void parentRedirections() override;
};
        
#endif
