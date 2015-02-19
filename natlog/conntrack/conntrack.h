#ifndef INCLUDED_CONNTRACK_
#define INCLUDED_CONNTRACK_

#include <iosfwd>

#include <bobcat/pattern>
#include <bobcat/signal>
#include <bobcat/fork>
#include <bobcat/pipe>

#include "../conntrackrecord/conntrackrecord.h"

class Options;

class Conntrack: public FBB::Fork, public FBB::SignalHandler
{
    FBB::Pipe d_pipe;
    ConntrackRecord d_connections;
    Options &d_options;
    std::ostream &d_stdMsg;
    bool d_stop = false;
    std::string d_accept;

    public:
        Conntrack(std::ostream &stdMsg);
        ~Conntrack();
        void run();

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

        void parentProcess() override;
        void childProcess() override;
        void childRedirections() override;
        void parentRedirections() override;

        bool accept(std::string const &protocol) const;
};
        
#endif







