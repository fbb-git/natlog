#ifndef INCLUDED_NATFORK_
#define INCLUDED_NATFORK_

#include <ostream>

#include <bobcat/fork>
#include <bobcat/multistreambuf>
#include <bobcat/pipe>


class NatFork: public FBB::Fork
{
    enum Mode
    {
        CONNTRACK,
        PCAP
    };

    FBB::MultiStreambuf d_msb;
    std::ostream d_out;
    Mode d_mode;
    FBB::Pipe d_pipe;

    public:
        NatFork();

        void run();

    private:
        virtual void parentProcess() override;
        virtual void childProcess() override;
};
        
#endif
