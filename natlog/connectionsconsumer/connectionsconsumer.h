#ifndef INCLUDED_CONNECTIONSCONSUMER_
#define INCLUDED_CONNECTIONSCONSUMER_

#include <iosfwd>
#include <unordered_map>
#include <mutex>
#include <fstream>

#include "../record/record.h"

class Storage;

    // ConnectionsConsumer object constructed in natfork/childprocess
class ConnectionsConsumer
{
    typedef std::unordered_map<size_t, Record> RecordMap;
    typedef RecordMap::value_type value_type;

    std::ofstream d_logDataStream;
    std::ostream &d_stdMsg;
    Storage &d_storage;

    std::mutex d_icmpMutex;
    RecordMap d_icmp;

    std::mutex d_udpMutex;
    RecordMap d_udp;

    std::unordered_map<size_t, size_t> d_sequence;  // TCP: sequence nr -> key
    std::unordered_map<size_t, size_t> d_id;        // UDP: id nr -> key

    std::mutex d_tcpMutex;
    RecordMap d_tcp;

    void (ConnectionsConsumer::*d_logData)(Record const &, char const*);

    static std::unordered_map<
                    Record::Protocol, 
                    void (ConnectionsConsumer::*)(Record &)
                > s_handler;

    time_t  d_ttl;

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
        void icmpOut(Record const &record);

        void tcpIn(Record &record);
        void udpIn(Record &record);

        void tcpOut(Record &record);
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

        static void cleanupWrap(ConnectionsConsumer *const consumer);

        void cleanupICMP_UDP(time_t now_ttl);   // clean up completed 
                                                // connections.
        void cleanup(
            time_t now_ttl, std::mutex &mapMutex, RecordMap &map,
            void (ConnectionsConsumer::*logFun)(Record const &, char const *),
            char const *type
        );
};
        
#endif




