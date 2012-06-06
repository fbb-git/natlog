#ifndef INCLUDED_CONNTRACK_
#define INCLUDED_CONNTRACK_

#include <bobcat/process>
#include <bobcat/syslogstream>

class Options;

class Conntrack
{
    Options &d_options;
    FBB::Process d_conntrack;
    FBB::SyslogStream d_syslog;

    public:
        Conntrack();
        void run();

    private:
};
        
#endif
