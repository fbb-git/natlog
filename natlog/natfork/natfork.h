#ifndef INCLUDED_NATFORK_
#define INCLUDED_NATFORK_

#include <fstream>

#include <bobcat/fork>
#include <bobcat/multistreambuf>

#include "../options/options.h"
#include "../rotatingstream/rotatingstream.h"

namespace FBB
{
    class SyslogStream;
}

class Producer;
class Storage;

class NatFork: public FBB::Fork
{
    Options &d_options;

    std::unique_ptr<FBB::SyslogStream> d_syslog;
    RotatingStream d_log;

    FBB::MultiStreambuf d_multiStreambuf;
    std::ostream d_stdMsg;

    Options::Mode d_mode;

    static Producer *(*s_producer[]) (std::ostream &stdMsg, Storage &storage);

    public:
        NatFork();                  // configure and initialize data
        ~NatFork() override;

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
