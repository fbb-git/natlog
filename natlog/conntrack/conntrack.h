#ifndef INCLUDED_CONNTRACK_
#define INCLUDED_CONNTRACK_

#include <unordered_map>

#include <bobcat/process>
#include <bobcat/syslogstream>
#include <bobcat/pattern>

class Options;

class Conntrack
{
    std::unordered_map<std::string, FBB::Pattern> d_record;
    typedef std::unordered_map<std::string, FBB::Pattern>::iterator Iterator;

    Options &d_options;
    FBB::Process d_conntrack;
    FBB::SyslogStream d_syslog;
    std::string d_utcMarker;

    static FBB::Process *s_conntrack;

    public:
        Conntrack();
        ~Conntrack();
        void run();

    private:
        void out(FBB::Pattern const &pat, std::string const &endSeconds, 
                                          std::string const &endMicroSecs);

        static void handler(int);
};
        
#endif

