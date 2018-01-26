#ifndef INCLUDED_RECORD_
#define INCLUDED_RECORD_

#include <string>
#include <ctime>

#include "../iptypes/iptypes.h"

// all connection data are available in Record. Derived classes 
// themselves have no relevant data.

struct Record: public IP_Types
{
        // == and != are implemented for use by unordered_maps. They only
        // compare source and destination ports.

    friend bool operator==(Record const &lhs, Record const &rhs);

    enum Type
    {
        IN,
        OUT,

        NEW,            // Conntrack types 
        DESTROY,
    };

    private:
        Protocol d_protocol;
        Type d_type;

        size_t d_key;
    
        size_t d_seconds = 0;
        size_t d_microSeconds = 0;
    
        size_t d_inSeconds;
        size_t d_inMicroSeconds;
    
        size_t d_sourceIP;
        size_t d_viaIP;
        size_t d_destIP;
    
        size_t  d_sourcePort = 0;
        size_t  d_viaPort;
        size_t  d_destPort = 0;

        size_t  d_receivedBytes = 0;
        size_t  d_sentBytes = 0;
        size_t  d_payload = 0;
    
        size_t  d_flags;
        size_t  d_id;               // sequence nr for TCP, identification for
                                    // UDP
        time_t  d_lastUsed;

    public:
        Record() = default;         // required for Storage and ConntrackRec.
        virtual ~Record();

        // move and copy operations: all default

        Protocol protocol() const; 
        char const *protocolStr() const;

        Type type() const; 

        size_t key() const;
        size_t setTCPUDPkey();

        size_t id() const;          // with ICMP

        size_t inSeconds() const;
        size_t seconds() const;
        size_t muSeconds() const;

        std::string beginTime() const;
        std::string endTime() const;
        bool hasEndTime() const;

        std::string sourceIPstr() const;
        std::string viaIPstr() const;
        std::string destIPstr() const;

        size_t sourceIP() const;
        size_t viaIP() const;
        size_t destIP() const;

        size_t  sourcePort() const;
        size_t  viaPort() const;
        size_t  destPort() const;

        size_t  receivedBytes() const;
        size_t  sentBytes() const;
        size_t  payload() const;

        size_t  flags() const;          // only with TCP

        std::string showFlags() const;

        time_t lastUsed() const;

    // public modifiers:
        void addReceivedBytes(size_t  receivedBytes);
        void addSentBytes(size_t  sentBytes);

        void setViaIP(size_t viaIP);        // used in connections/udp.cc
        void setViaPort(size_t  viaPort);
        void setEndTime(Record const &record);
        void reverse();                     // swap source and dest stuff

    protected:
                                    // used for pcap and tcpdump records
        Record(Type type, size_t seconds, size_t muSeconds,
                u_char const *packet);

        void setProtocol(Protocol protocol);
        void setType(Type type);
        void setLastUsed(time_t time);

        void setKey(size_t key);

        void setTime(size_t seconds, size_t microSeconds);

        void setSourceIP(size_t sourceIP);
        void setDestIP(size_t destIP);

        void setPorts(size_t sourcePort, size_t destPort);

        static size_t aton(std::string const &addr);
        static std::string time(size_t seconds, size_t microSeconds);

    private:
        static char *ntoa(uint32_t ipAddr);
        static size_t ports2key(size_t lowPort, size_t highPort);
};

inline size_t Record::key() const
{
    return d_key;
}

inline size_t Record::id() const
{
    return d_id;
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


inline size_t Record::flags() const       // only with TCP
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

inline void Record::setKey(size_t key)
{
    d_key = key;
}

inline void Record::setTime(size_t seconds, size_t microSeconds)
{
    d_inSeconds = seconds;
    d_inMicroSeconds = microSeconds;
}

inline void Record::setEndTime(Record const &other)
{
    d_seconds = other.d_inSeconds;
    d_microSeconds = other.d_inMicroSeconds;
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

inline bool operator!=(Record const &lhs, Record const &rhs)
{
    return not (lhs == rhs);
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

#endif
