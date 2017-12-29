#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <string>

#include <bobcat/argconfig>
#include <bobcat/syslogstream>      // for the enums
#include <bobcat/linearmap>

struct Options
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
        CONNTRACK_ENDED,
    };
    
    private:
        FBB::ArgConfig &d_arg;
    
        bool d_daemon;
        bool d_stdout;
        bool d_useSyslog;
        bool d_warnings;

        size_t d_verbose;
        size_t d_conntrackRestart = 10;

        FBB::LinearMap<std::string, Time>::const_iterator d_time;
    
        std::string d_conntrackCommand;
        std::string d_conntrackDevice;
        std::string d_configPath;
        std::string d_syslogTag;
        std::string d_PIDfile;
        std::string d_timeSpecError;
        std::string d_syslogPriorityError;
        std::string d_syslogFacilityError;
        std::string d_conntrackProtocol;
    
        FBB::LinearMap<std::string, FBB::Facility>::const_iterator 
                                                            d_syslogFacility;
        FBB::LinearMap<std::string, FBB::Priority>::const_iterator 
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
    
        static FBB::LinearMap<std:: string, Time> const s_time;
        static FBB::LinearMap<std::string, FBB::Facility> const 
                                                           s_syslogFacilities;
        static FBB::LinearMap<std::string, FBB::Priority> const 
                                                           s_syslogPriorities;

        static Options *s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        bool daemon() const;
        bool stdout() const;
        bool syslog() const;
        bool warnings() const;

        size_t verbose() const;

        Time time() const;
        std::string const &timeTxt() const;

        std::string const &configPath() const;
        std::string const &timeSpecError() const;
        std::string const &pidFile() const;
        std::string const &protocols() const;
        std::string const &conntrackCommand() const;
        char const *conntrackDevice() const;
        std::string const &syslogTag() const;

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

        static char const *defaultConfigPath();
        static char const *defaultConntrackCommand();
        static char const *defaultConntrackArgs();
        static char const *defaultSyslogIdent();
        static char const *defaultSyslogFacility();
        static char const *defaultSyslogPriority();
        static char const *defaultPIDfile();

    private:
        Options();

        void openConfig();
        void setSyslogParams();
        void setBoolMembers();
        void setSyslogFacility();
        void setSyslogPriority();
        void setTime(std::string const &time);

        std::string protocol(std::string const &available, std::string &spec);
        std::string setProtocol();
};

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

inline bool Options::warnings() const
{   
    return d_warnings;
}

inline bool Options::syslog() const
{   
    return d_useSyslog;
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

inline std::string const &Options::protocols() const
{
    return d_conntrackProtocol;
}

#endif






