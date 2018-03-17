#ifndef INCLUDED_RECORD_
#define INCLUDED_RECORD_

#include <iosfwd>
#include <string>
#include <ctime>
#include <memory>

#include "../iptypes/iptypes.h"

// all connection data are available in Record. Derived classes 
// themselves have no relevant data.

struct Record: public IP_Types
{
        // == and != are implemented for use by unordered_maps. They only
        // compare source and destination ports.

    friend std::ostream &operator<<(std::ostream &out, Record const &record);

    enum Type           // update ../nic/ when altered.
    {
        IN,
        OUT,

        NEW,            // Conntrack types 
        DESTROY
    };

    enum 
    {
        nTypes = DESTROY + 1
    };

    private:
        union Key
        {
            struct
            {
                uint32_t v32;
                uint16_t v16;
            };
            uint64_t key;
        };
    
        Protocol d_protocol;
        Type d_type;

        Key d_key = {0};
        size_t d_id = 0;            // ID with UDP, sequence with TCP
    
        size_t d_seconds = 0;
        size_t d_microSeconds = 0;
    
        size_t d_inSeconds;
        size_t d_inMicroSeconds;
    
        uint32_t d_sourceIP = 0;
        uint32_t d_viaIP = 0;
        uint32_t d_destIP = 0;
    
        uint16_t  d_sourcePort = 0;
        uint16_t  d_viaPort = 0;
        uint16_t  d_destPort = 0;

        size_t  d_receivedBytes = 0;
        size_t  d_sentBytes = 0;
        size_t  d_payload = 0;
        size_t  d_flags = 0;

        time_t  d_lastUsed;

        static size_t s_count;

    public:
        virtual ~Record();

        Record(Record const &other) = delete;

        Protocol protocol() const;          // i
        char const *protocolStr() const;

        Type type() const;          // i

        uint64_t key() const;               // i    - actual key
        uint64_t srcKey() const;            // i    - from src
        uint64_t dstKey() const;            // i    - from dst
    
        size_t inSeconds() const;   // i
        size_t seconds() const;     // i
        size_t muSeconds() const;   // i

        std::string beginTime() const;
        std::string endTime() const;
        bool hasEndTime() const;

        std::string sourceIPstr() const;    // i
        std::string viaIPstr() const;       // i
        std::string destIPstr() const;      // i

        size_t sourceIP() const;            // i
        size_t viaIP() const;               // i
        size_t destIP() const;              // i

        size_t  sourcePort() const;         // i
        size_t  viaPort() const;            // i
        size_t  destPort() const;           // i

        size_t  receivedBytes() const;      // i
        size_t  sentBytes() const;          // i
        size_t  payload() const;            // i
        size_t  id() const;                 // i    used by UDP/TCP
        size_t  flags() const;              // i    - only with TCP

        std::string showFlags() const;

        time_t lastUsed() const;

    // public modifiers:
        void addReceivedBytes(Record const &next);
        void addSentBytes(Record const &next);

        void setVia(uint64_t key);
        void setViaIP(size_t viaIP);        // used in connections/udp.cc
        void setViaPort(size_t  viaPort);
        void setSrcKey();                       // i    - from src

        static size_t count();

    protected:
                                    // used for pcap and tcpdump records
        Record(Type type, size_t seconds, size_t muSeconds,
                u_char const *packet);
        Record();                   // 2.cc - used by ConntrackRecord

        void setReceivedBytes(size_t nBytes);   // i
        void setSentBytes(size_t nBytes);       // i

        void setProtocol(Protocol protocol);    // i
        void setType(Type type);                // i
        void setLastUsed(time_t time);

        void setTime(size_t seconds, size_t microSeconds);
        void setAllTimes(size_t seconds, size_t microSeconds);

        void setSourceIP(size_t sourceIP);      // i
        void setDestIP(size_t destIP);          // i

        void setPorts(size_t sourcePort, size_t destPort);      

        static size_t aton(std::string const &addr);
        static std::string time(size_t seconds, size_t microSeconds);

        void setIDKey(uint32_t id, uint16_t seq);   // i    - set d_id and key

    private:
        void setEndTime(Record const &record);  // also updates d_lastUsed
        std::ostream &insertInto(std::ostream &out) const;

        static char *ntoa(uint32_t ipAddr);
};

typedef std::unique_ptr<Record> RecordPtr;

// static
inline size_t Record::count()
{
    return s_count;
}

inline uint64_t Record::key() const
{
    return d_key.key;
}

inline uint64_t Record::srcKey() const
{
    return Key{ { d_sourceIP, d_sourcePort } }.key;
}

inline uint64_t Record::dstKey() const
{
    return Key{ { d_destIP, d_destPort } }.key;
}

inline Record::Protocol Record::protocol() const
{
    return d_protocol;
}

inline Record::Type Record::type() const
{
    return d_type;
}

inline size_t Record::seconds() const
{
    return d_seconds;
}

inline size_t Record::inSeconds() const
{
    return d_inSeconds;
}

inline size_t Record::muSeconds() const
{
    return d_microSeconds;
}

inline std::string Record::sourceIPstr() const
{
    return ntoa(d_sourceIP);
}

inline size_t Record::sourceIP() const
{
    return d_sourceIP;
}

inline size_t Record::destIP() const
{
    return d_destIP;
}

inline size_t Record::viaIP() const
{
    return d_viaIP;
}

inline std::string Record::viaIPstr() const
{
    return ntoa(d_viaIP);
}

inline std::string Record::destIPstr() const
{
    return ntoa(d_destIP);
}

inline size_t  Record::sourcePort() const
{
    return d_sourcePort;
}

inline size_t  Record::viaPort() const
{
    return d_viaPort;
}

inline size_t  Record::destPort() const
{
    return d_destPort;
}

inline size_t  Record::receivedBytes() const
{
    return d_receivedBytes;
}

inline size_t  Record::sentBytes() const
{
    return d_sentBytes;
}

inline size_t Record::payload() const
{
    return d_payload;
}

inline size_t Record::id() const        // TCP / UDP
{
    return d_id;
}

inline size_t Record::flags() const     // only with TCP
{
    return d_flags;
}

inline void Record::setProtocol(Protocol protocol) 
{
    d_protocol = protocol;
}

inline void Record::setType(Type type) 
{
    d_type = type;
}

inline void Record::setSourceIP(size_t sourceIP)
{
    d_sourceIP = sourceIP;
}

inline void Record::setViaIP(size_t viaIP)
{
    d_viaIP = viaIP;
}

inline void Record::setDestIP(size_t destIP)
{
    d_destIP = destIP;
}

inline void Record::setViaPort(size_t  viaPort)
{
    d_viaPort = viaPort;
}

inline time_t Record::lastUsed() const
{
    return d_lastUsed;
}

inline std::string Record::beginTime() const
{
    return time(d_inSeconds, d_inMicroSeconds);
}

inline std::string Record::endTime() const
{
    return time(d_seconds, d_microSeconds);
}

inline bool Record::hasEndTime() const
{
    return d_seconds != 0;
}

inline void Record::setLastUsed(time_t time)
{
    d_lastUsed = time;
}

inline void Record::setSentBytes(size_t size)
{
    d_sentBytes = size;
}

inline void Record::setReceivedBytes(size_t size)
{
    d_receivedBytes = size;
}

inline void Record::setIDKey(uint32_t id, uint16_t seq)
{
    d_key = Key{id, seq};
}

inline void Record::setSrcKey()
{
    d_key = Key{ { d_sourceIP, d_sourcePort } };
}

inline std::ostream &operator<<(std::ostream &out, Record const &record)
{
    return record.insertInto(out);
}

#endif
