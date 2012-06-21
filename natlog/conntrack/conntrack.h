#ifndef INCLUDED_CONNTRACK_
#define INCLUDED_CONNTRACK_

#include <iosfwd>

#include <bobcat/process>
#include <bobcat/pattern>

#include "../signal/signal.h"
#include "../conntrackrecord/conntrackrecord.h"

class Options;

class Conntrack: public SignalHandler
{
    ConntrackRecord d_connections;
    Options &d_options;
    FBB::Process d_conntrack;
    std::ostream &d_stdMsg;

    public:
        Conntrack(std::ostream &stdMsg);
        ~Conntrack();
        void run(std::ostream &parent);

    private:
        void log(ConntrackRecord::Record const &record, 
                    std::string const &endSeconds, 
                    std::string endMicroSecs);

        virtual void signaled(size_t signum) override;
};
        
#endif

