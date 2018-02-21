#ifndef INCLUDED_CONNECTIONSCONSUMER_
#define INCLUDED_CONNECTIONSCONSUMER_

#include <iosfwd>
#include <unordered_map>

#include <bobcat/signal>

#include "../rotatingstream/rotatingstream.h"
#include "../icmp/icmp.h"
#include "../udp/udp.h"
#include "../tcp/tcp.h"
#include "../record/record.h"

class Storage;
class Options;

    // ConnectionsConsumer object constructed in natfork/childprocess
class ConnectionsConsumer: public FBB::SignalHandler
{
    Options const &d_options;

    RotatingStream d_logDataStream;
    std::ostream &d_stdMsg;
    Storage &d_storage;

    ICMP d_icmp;
    UDP d_udp;
    TCP d_tcp;

    std::unordered_map< Record::Protocol, IPbase * > d_handler;

    time_t  d_ttl;

    public:
        ConnectionsConsumer(std::ostream &stdMsg, Storage &storage);

        void run();                         // process all connections:
                                            // start the producer thread
                                            // and consume the produced data
    private:
        void signalHandler(size_t signum) override;             // i

        static void cleanupWrap(ConnectionsConsumer *consumer);

        void cleanupICMP_UDP(time_t now_ttl);   // clean up completed 
                                                // connections.
        static void header(std::ostream &log);
};

#endif




