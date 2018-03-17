#ifndef INCLUDED_IPBASE_
#define INCLUDED_IPBASE_

#include <iosfwd>
#include <unordered_map>
#include <mutex>

#include "../record/record.h"

    // received RecordPtr objects are passed on to function that may grab
    // their contents. Otherwise, the Record as const & is passed to the
    // called function: destruction is then handled by the unique_ptr's
    // destruction 

struct IPbase
{
    enum LogType
    {
        COMPLETE,
        EXPIRED,
        EOP
    };

    private:
        std::ostream &d_stdMsg;
        std::ostream &d_logDataStream;
    
        typedef std::unordered_map<uint64_t, RecordPtr> RecordMap;

        std::mutex d_mutex;
        RecordMap d_map;
    
        void (IPbase::*d_logData)(Record const &) const;
    
        static LogType  s_logType;
        static std::pair<char const *, char const *> s_logTypeText[];
    
    public:
        virtual ~IPbase();

        void process(RecordPtr next);       // starting point: received from 
                                            // ConnectionsConsumer::run
        void cleanup(time_t now_ttl);

        static void setLogType(LogType logType);
        static std::pair<char const *, char const *> const &logType();

    protected:
                    // KeyMap is used to associate the OUT dev. packets
                    // with available IN dev packets in UDP/TCP connections
                    // at a syn-packet 'expired' is set true: cleanupHook 
                    // may remove the keyMap value at cleanup time.
                    // At an outDev packet, if the ID is new, 'expired' is set
                    // false: maybe the next SYN packet immediately follows.
        struct KeyMapStruct
        {
            bool        expired;
            uint64_t    key;
        };
        typedef std::unordered_map<size_t, KeyMapStruct> KeyMap;

        IPbase(std::ostream &stdMsg, std::ostream &logDataStream);

        size_t size() const;
        void insert(RecordPtr &next);

        RecordMap::iterator find(uint64_t key);
        RecordMap::iterator end();

        void logCSV(Record const &record) const;

                                                // also deletes the Record
        void erase(RecordMap::iterator const &iter);

        std::ostream &stdMsg() const;

        void setVia(RecordMap::iterator const &iter, Record const &next);

        void log(Record const &record) const;   

        void keyMapCleanup(KeyMap &keyMap);

        void maybeSizeLog(size_t *lastSize, size_t keyMapSize, 
                          char const *label);

    private:
        virtual void cleanupHook();        

            // default: TCP and UDP records
        virtual void logConnection(Record const &record) const;

        virtual void inDev(RecordPtr &next);        // TCP overrides

        virtual void sent(RecordPtr &next) = 0;
        virtual void received(RecordPtr &next) = 0;

        virtual void outDev(RecordPtr &next) = 0; 

        void destroy(Record const &record);  
        void logData(Record const &record) const;
        void noDataLog(Record const &record) const;
};

inline size_t IPbase::size() const
{
    return d_map.size();
}

inline void IPbase::insert(RecordPtr &next)
{
    d_map.insert( { next->key(), std::move(next) } );
}

inline IPbase::RecordMap::iterator IPbase::end()
{
    return d_map.end();
}

inline IPbase::RecordMap::iterator IPbase::find(uint64_t key)
{
    return d_map.find(key);
}

inline void IPbase::logCSV(Record const &record) const
{
    (this->*d_logData) (record);
}

inline std::ostream &IPbase::stdMsg() const
{
    return d_stdMsg;
}

// static
inline std::pair<char const *, char const *> const &IPbase::logType()
{
    return s_logTypeText[s_logType];
}

// static
inline void IPbase::setLogType(LogType logType)
{
    if (s_logType != EOP)
        s_logType = logType;
}

#endif





