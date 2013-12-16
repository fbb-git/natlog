#ifndef INCLUDED_CONNTRACK_
#define INCLUDED_CONNTRACK_

#include <iosfwd>

#include <bobcat/process>
#include <bobcat/pattern>
#include <bobcat/signal>

#include "../conntrackrecord/conntrackrecord.h"

class Options;

class Conntrack: public FBB::SignalHandler
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
        bool tcpudpConnection(FBB::Pattern const &tcpudp);
        bool icmpConnection(FBB::Pattern const &tcpudp);

        void logTcpudp(ConntrackRecord::Record const &record, 
                    std::string const &endSeconds, 
                    std::string endMicroSecs);
        void logIcmp(ConntrackRecord::Record const &record, 
                    std::string const &endSeconds, 
                    std::string endMicroSecs);

        void signalHandler(size_t signum) override;
};
        
#endif

