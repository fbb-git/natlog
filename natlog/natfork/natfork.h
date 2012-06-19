#ifndef INCLUDED_NATFORK_
#define INCLUDED_NATFORK_

#include <ostream>
#include <memory>

#include <bobcat/fork>
#include <bobcat/multistreambuf>
#include <bobcat/pipe>


namespace FBB
{
    class SyslogStream;
}

class Options;

class NatFork: public FBB::Fork
{
    enum Mode
    {
        CONNTRACK,
        PCAP
    };

    Options &d_options;

    std::unique_ptr<FBB::SyslogStream> d_syslog;

    FBB::MultiStreambuf d_msb;
    std::ostream d_out;

    Mode d_mode;
    FBB::Pipe d_pipe;

    public:
        NatFork();

        void run();

    private:
        void configureMsb();
        void conntrackMode();

        virtual void parentProcess() override;
        virtual void childProcess() override;
};
        
#endif
