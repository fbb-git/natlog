#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <ctime>
#include <string>
#include <unordered_set>

#include <bobcat/argconfig>
#include <bobcat/syslogstream>      // for the enums

#include "../iptypes/iptypes.h"

struct Options: public IP_Types
{
    enum Time
    {
        RAW,
        UTC,
        LT
    };

    enum ExitStatus
    {
        OK,
        FAILED,
        TERM_SIGNAL,
    };
    
    enum Mode               // working mode: conntrack, pcap, or tcpdump
    {
        CONNTRACK,          // when modified: update producer/data.cc
        DEVICE,
        TCPDUMP,
    };

    enum 
    {
        TTL = 60,           // default TTL in seconds
        TTL_TCP = 3000      // TTL for TCP
    };

    private:
        FBB::ArgConfig &d_arg;
    
        bool d_daemon;
        bool d_stdout;
        bool d_terminate;

        Mode d_mode;

        size_t d_IPheaderSize = 0;
        size_t d_verbose;
        size_t d_conntrackRestart = 10;

        size_t d_rotateFreq = 0;        // rotate non-syslog logs
        size_t d_rotateFactor = 1;      // after spec * factor minutes
        std::string d_rotateTimeSpec;   // e.g., ' minutes'

        size_t d_nRotations = 0;        // rotate #files

        time_t d_ttl = TTL;
        time_t d_ttlTCP = TTL_TCP;
        
        std::unordered_map<std::string, Time>::const_iterator d_time;
    
        std::string d_conntrackCommand;
        std::string d_conntrackDevice;
        std::string d_configPath;
        std::string d_syslogTag;
        std::string d_PIDfile;
        std::string d_timeSpecError;
        std::string d_syslogPriorityError;
        std::string d_syslogFacilityError;
        std::string d_log;
        std::string d_logData;

        std::unordered_set<Protocol> d_protocols;
    
        std::unordered_map<std::string, FBB::Facility>::const_iterator 
                                                            d_syslogFacility;
        std::unordered_map<std::string, FBB::Priority>::const_iterator 
                                                            d_syslogPriority;
            // default values:

        static char const s_defaultConfigPath[];
        static char const s_defaultConntrackCommand[];
        static char const s_defaultConntrackDevice[];
        static char const s_defaultConntrackArgs[];
        static char const s_defaultSyslogIdent[];
        static char const s_defaultSyslogFacility[];
        static char const s_defaultSyslogPriority[];
        static char const s_defaultPIDfile[];
    
        static std::unordered_map<std:: string, Time> const s_time;
        static std::unordered_map<std::string, FBB::Facility> const 
                                                           s_syslogFacilities;
        static std::unordered_map<std::string, FBB::Priority> const 
                                                           s_syslogPriorities;
        static std::unordered_map<std::string, Protocol> const 
                                                           s_name2protocol;
        static std::unordered_map<Protocol, std::string> const 
                                                           s_protocol2name;

        static Options *s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        bool daemon() const;
        void foreground();              // undo a default daemon request

        bool realTime() const;          // true if the packets are received
                                        // real-time; when recorded: false.
        bool stdout() const;
        bool kill() const;

        size_t IPheaderSize() const;
        size_t verbose() const;

        size_t rotateFreq() const;
        size_t rotateFactor() const;
        size_t nRotations() const;
        std::string const &rotateTimeSpec() const;

        time_t ttl() const;
        time_t ttlTCP() const;

        Time time() const;
        std::string const &timeTxt() const;
        Mode mode() const;

        std::string const &configPath() const;
        std::string const &timeSpecError() const;
        std::string const &pidFile() const;
        std::unordered_set<Protocol> const &protocolSet() const;
        bool hasProtocol(std::string const &protoName) const;
        bool hasProtocol(size_t protocol) const;
        std::string const &conntrackCommand() const;
        char const *conntrackDevice() const;
        std::string const &syslogTag() const;
        std::string const &log() const;
        std::string const &logData() const;

        FBB::Priority syslogPriority() const;
        FBB::Facility syslogFacility() const;

        std::string const &priority() const;
        std::string const &facility() const;

        std::string syslogPriorityError() const;
        std::string syslogFacilityError() const;

        char const *operator[](size_t idx) const;   // forwards ArgConfig's
        size_t nArgs() const;                       // values.
        std::string const &basename() const;

        size_t  conntrackRestart() const;

        std::string protocolNames() const;

        static std::string const &protocolName(Protocol protocol);
        static char const *defaultConfigPath();
        static char const *defaultConntrackCommand();
        static char const *defaultConntrackDevice();
        static char const *defaultConntrackArgs();
        static char const *defaultSyslogIdent();
        static char const *defaultSyslogFacility();
        static char const *defaultSyslogPriority();
        static char const *defaultPIDfile();

    private:
        Options();

        void openConfig();
        void setBoolMembers();
        void setConntrack();
        void setMode();
        void setLogParams();
        void setSyslogFacility();
        void setSyslogPriority();
        void setTimeType(std::string const &time);
        void setTimeSpec();
        void setProtocol();
};

inline Options::Mode Options::mode() const
{   
    return d_mode;
}

inline bool Options::realTime() const
{
    return d_mode != TCPDUMP;
}

inline bool Options::stdout() const
{   
    return d_stdout;
}

inline size_t Options::verbose() const
{   
    return d_verbose;
}

inline bool Options::daemon() const
{   
    return d_daemon;
}

inline void Options::foreground()
{   
    d_daemon = false;
}

inline std::string const &Options::log() const
{   
    return d_log;
}

inline size_t Options::rotateFreq() const
{
    return d_rotateFreq;
}

inline size_t Options::rotateFactor() const
{
    return d_rotateFactor;
}

inline std::string const &Options::rotateTimeSpec() const
{
    return d_rotateTimeSpec;
}

inline size_t Options::nRotations() const
{
    return d_nRotations;
}

inline time_t Options::ttl() const
{
    return d_ttl;
}

inline time_t Options::ttlTCP() const
{
    return d_ttlTCP;
}

inline size_t Options::IPheaderSize() const
{
    return d_IPheaderSize;
}

inline Options::Time Options::time() const
{   
    return d_time->second;
}

inline std::string const &Options::timeTxt() const
{   
    return d_time->first;
}

inline std::string const &Options::configPath() const
{   
    return d_configPath;
}

inline std::string const &Options::syslogTag() const
{   
    return d_syslogTag;
}

inline std::string const &Options::logData() const
{   
    return d_logData;
}

//inline size_t Options::logDataFlush() const
//{   
//    return d_logDataFlush;
//}

inline std::string const &Options::pidFile() const
{   
    return d_PIDfile;
}

inline std::string const &Options::timeSpecError() const
{   
    return d_timeSpecError;
}

inline FBB::Priority Options::syslogPriority() const
{   
    return d_syslogPriority->second;
}

inline std::string const &Options::priority() const
{   
    return d_syslogPriority->first;
}

inline std::string Options::syslogPriorityError() const
{   
    return d_syslogPriorityError;
}

inline FBB::Facility Options::syslogFacility() const
{   
    return d_syslogFacility->second;
}

inline std::string Options::syslogFacilityError() const
{   
    return d_syslogFacilityError;
}

inline char const *Options::defaultPIDfile() 
{
    return s_defaultPIDfile;
}

inline char const *Options::defaultConfigPath() 
{
    return s_defaultConfigPath;
}

inline std::string const &Options::facility() const
{   
    return d_syslogFacility->first;
}

inline std::string const &Options::conntrackCommand() const
{
    return d_conntrackCommand;
}

inline char const *Options::conntrackDevice() const
{
    return d_conntrackDevice.c_str();
}

inline char const *Options::operator[](size_t idx) const
{
    return d_arg[idx];
}

inline size_t Options::nArgs() const
{
    return d_arg.nArgs();
}

inline std::string const &Options::basename() const
{
    return d_arg.basename();
}

inline char const *Options::defaultConntrackCommand() 
{
    return s_defaultConntrackCommand;
}

inline char const *Options::defaultConntrackDevice() 
{
    return s_defaultConntrackDevice;
}

inline char const *Options::defaultSyslogIdent() 
{
    return s_defaultSyslogIdent;
}

inline char const *Options::defaultSyslogFacility() 
{
    return s_defaultSyslogFacility;
}

inline char const *Options::defaultSyslogPriority() 
{
    return s_defaultSyslogPriority;
}

inline size_t Options::conntrackRestart() const
{
    return d_conntrackRestart;
}

inline std::unordered_set<IP_Types::Protocol> const &Options::protocolSet() 
                                                                        const
{
    return d_protocols;
}

inline std::string const &Options::protocolName(Protocol protocol)
{
    return s_protocol2name.find(protocol)->second;
}

inline bool Options::hasProtocol(size_t protocol) const
{
    return d_protocols.find(static_cast<Protocol>(protocol))
            != d_protocols.end(); 
}

#endif
