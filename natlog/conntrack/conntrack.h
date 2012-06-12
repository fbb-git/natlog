#ifndef INCLUDED_CONNTRACK_
#define INCLUDED_CONNTRACK_

#include <unordered_map>

#include <bobcat/process>
#include <bobcat/pattern>

#include "../signal/signal.h"

class Options;

namespace FBB
{
    class SyslogStream;
}

class Conntrack: public SignalHandler
{
    std::unordered_map<std::string, FBB::Pattern> d_record;
    typedef std::unordered_map<std::string, FBB::Pattern>::iterator Iterator;

    Options &d_options;
    FBB::Process d_conntrack;
    FBB::SyslogStream &d_syslog;
    std::string d_utcMarker;

    public:
        Conntrack(FBB::SyslogStream &syslog);
        ~Conntrack();
        void run();

    private:
        void out(FBB::Pattern const &pat, std::string const &endSeconds, 
                                          std::string const &endMicroSecs);

        virtual void signaled(size_t signum) override;
};
        
#endif

