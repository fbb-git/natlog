#ifndef INCLUDED_IPBASE_
#define INCLUDED_IPBASE_

#include <iosfwd>
#include <unordered_map>
#include <mutex>

#include "../record/record.h"

struct IPbase
{
    enum LogType
    {
        COMPLETE,
        INCOMPLETE,
        EOP
    };

    private:
        std::ostream &d_stdMsg;
        std::ostream &d_logDataStream;
    
        typedef std::unordered_map<uint64_t, Record *> RecordMap;
        typedef RecordMap::value_type value_type;
    
        std::mutex d_mutex;
        RecordMap d_map;
    
        void (IPbase::*d_logData)(Record const *) const;
    
        static LogType  s_logType;
        static std::pair<char const *, char const *> s_logTypeText[];
    
    public:
        virtual ~IPbase();

        void process(Record *next);
        void cleanup(time_t now_ttl);

        static void setLogType(LogType logType);
        static std::pair<char const *, char const *> const &logType();

    protected:
        IPbase(std::ostream &stdMsg, std::ostream &logDataStream);

        size_t size() const;
        void insert(uint64_t key, Record *next);

        RecordMap::iterator find(uint64_t key);
        RecordMap::iterator end();

        void logCSV(Record const *record) const;

                                                // also deletes the Record
        void erase(RecordMap::iterator const &iter);

        std::ostream &stdMsg() const;

                                                // also sets via-info        
        void newKey(RecordMap::iterator const &iter, Record const *next);

        void log(Record const *record) const;   
       
    private:
                                        // default: logs TCP and UDP records
        virtual void logConnection(Record const *record) const;

                                                        // UDP/TCP
        virtual void destroy(Record const *record);  

        virtual void inDev(Record *next);
        virtual void sent(Record *next);
        virtual void received(Record *next);

        virtual void outDev(Record const *next) = 0;

        void logData(Record const *record) const;
        void noDataLog(Record const *record) const;

};

inline size_t IPbase::size() const
{
    return d_map.size();
}

inline void IPbase::log(Record const *record) const
{
    logConnection(record);
}

inline void IPbase::insert(uint64_t key, Record *next)
{
    d_map.insert( value_type{ key, next } );
}

inline IPbase::RecordMap::iterator IPbase::end()
{
    return d_map.end();
}

inline IPbase::RecordMap::iterator IPbase::find(uint64_t key)
{
    return d_map.find(key);
}

inline void IPbase::logCSV(Record const *record) const
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





