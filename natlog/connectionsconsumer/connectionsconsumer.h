#ifndef INCLUDED_CONNECTIONSCONSUMER_
#define INCLUDED_CONNECTIONSCONSUMER_

#include <iosfwd>
#include <unordered_map>
#include <mutex>
#include <fstream>

#include <bobcat/signal>

#include "../record/record.h"
#include "../rotatingstream/rotatingstream.h"

class Storage;
class Options;

    // ConnectionsConsumer object constructed in natfork/childprocess
class ConnectionsConsumer: public FBB::SignalHandler
{
    typedef std::unordered_map<size_t, size_t> Size_tMap;

    typedef std::unordered_map<size_t, Record> RecordMap;
    typedef RecordMap::value_type value_type;

    Options const &d_options;

    RotatingStream d_logDataStream;
    std::ostream &d_stdMsg;
    Storage &d_storage;

    std::mutex d_icmpMutex;
    RecordMap d_icmp;

    std::mutex d_udpMutex;
    RecordMap d_udp;

    Size_tMap d_sequence;  // TCP: sequence nr -> key
    Size_tMap d_id;        // UDP: id nr -> key
    
    std::mutex d_tcpMutex;
    RecordMap d_tcp;

    void (ConnectionsConsumer::*d_logData)(Record const &, char const *);

    static std::unordered_map<
                    Record::Protocol, 
                    void (ConnectionsConsumer::*)(Record &)
                > s_handler;

    time_t  d_ttl;

    enum LogType
    {
        COMPLETE,
        INCOMPLETE,
        EOP
    };

    LogType  d_logType = COMPLETE;
    static std::pair<char const *, char const *> s_logType[];

    public:
        ConnectionsConsumer(std::ostream &stdMsg,Storage &storage);

        void run();                         // process all connections:
                                            // start the producer thread
                                            // and consume the produced data
    private:
        void icmp(Record &record);          // Producers must make sure that
        void tcp(Record &record);           // only defined protocols are
        void udp(Record &record);           // returned

        void icmpIn(Record &record);
        void tcpIn(Record &record);
        void udpIn(Record &record);

        void icmpOut(Record const &record);
        void tcpOut(Record const &record);
        void udpOut(Record const &record);

        void icmpDestroy(Record &record);   // used for conntrack connections
        void tcp_udpDestroy(RecordMap &map, Record const &record, 
                            char const *type);

        void tcpDestroy(Record &record);
        void udpDestroy(Record &record);

        void logICMP(Record const &record, char const *type = "");
        void logTCP_UDP(Record const &record, char const *type);

        void logData(Record const &record, char const *type);
        void noDataLog(Record const &record, char const *type);

        void signalHandler(size_t signum) override;

        static void cleanupWrap(ConnectionsConsumer *const consumer);

        void cleanupICMP_UDP(time_t now_ttl);   // clean up completed 
                                                // connections.
        void cleanup(
            time_t now_ttl, std::mutex &mapMutex, RecordMap &map,
            void (ConnectionsConsumer::*logFun)(Record const &, char const *),
            char const *type
        );

        static void header(std::ostream &log);
};

inline void ConnectionsConsumer::signalHandler(size_t signum)
{
    d_logType = EOP;
}
        
#endif




