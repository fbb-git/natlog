#ifndef INCLUDED_NATFORK_
#define INCLUDED_NATFORK_

#include <ostream>
#include <memory>

#include <bobcat/fork>
#include <bobcat/multistreambuf>

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

    FBB::MultiStreambuf d_multiStreambuf;
    std::ostream d_stdMsg;

    Mode d_mode;

    public:
        NatFork();

        void run();

    private:
        void setupStdMsg();
        void checkSyslogParam(char const *label, std::string const &actual, 
                                                 std::string const &err);
        void setupDaemonMsg();
        void setupNonDaemonMsg();

        void handleChildStatus();
        void conntrackMode();

        virtual void parentProcess() override;
        virtual void childProcess() override;
};
        
#endif
