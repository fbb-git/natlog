#ifndef INCLUDED_NATFORK_
#define INCLUDED_NATFORK_

#include <ostream>
#include <memory>

#include <bobcat/fork>
#include <bobcat/multistreambuf>

#include "../options/options.h"

namespace FBB
{
    class SyslogStream;
}

class NatFork: public FBB::Fork
{
    Options &d_options;

    std::unique_ptr<FBB::SyslogStream> d_syslog;

    FBB::MultiStreambuf d_multiStreambuf;
    std::ostream d_stdMsg;

    Options::Mode d_mode;

    public:
        NatFork();                  // configure and initialize data

        void run();                 // dameonize when running in the
                                    // background, otherwise call
                                    // 'childProcess'

    private:
        void specifications();

        void setupStdMsg();
        void checkSyslogParam(char const *label, std::string const &actual, 
                                                 std::string const &err);
        void setupDaemonMsg();
        void setupNonDaemonMsg();

        void handleChildStatus();
        void conntrackMode();

        void parentProcess() override;
        void childProcess() override;

        void cleanupPidFile() const;

};
        
#endif
