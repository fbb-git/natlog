#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <iostream>
#include <string>
#include <unordered_map>

#include <bobcat/syslogstream>
#include <bobcat/argconfig>

struct Options
{
    enum Time
    {
        RAW,
        UTC,
        LT
    };
    
    private:
        FBB::ArgConfig &d_arg;
    
        bool d_verbose;
        bool d_useSyslog;

        Time d_time;
    
        std::string d_conntrackPath;
        std::string d_syslogTag;
    
        std::unordered_map<std::string, FBB::Facility>::const_iterator 
                                                            d_syslogFacility;
        std::unordered_map<std::string, FBB::Priority>::const_iterator 
                                                            d_syslogPriority;
    
            // default values:

        static char const s_defaultConfigPath[];
        static char const s_defaultConntrackPath[];
        static char const s_defaultSyslogIdent[];
        static char const s_defaultSyslogFacility[];
        static char const s_defaultSyslogPriority[];
    
        static std::unordered_map<std:: string, Time> const s_time;
        static std::unordered_map<std::string, FBB::Facility> const 
                                                           s_syslogFacilities;
        static std::unordered_map<std::string, FBB::Priority> const 
                                                           s_syslogPriorities;

        static Options *s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        bool verbose() const;
        bool syslog() const;
        bool daemon();

        Time time() const;

        std::string const &conntrackPath() const;
        std::string const &syslogTag() const;

        FBB::Priority syslogPriority() const;
        FBB::Facility syslogFacility() const;

        std::string const &priority() const;
        std::string const &facility() const;

        static char const *defaultConfigPath();
        static char const *defaultConntrackPath();
        static char const *defaultSyslogIdent();
        static char const *defaultSyslogFacility();
        static char const *defaultSyslogPriority();

    private:
        Options();

        void setSyslogFacility();
        void setSyslogPriority();
        void setTime(std::string const &time);
};

inline bool Options::verbose() const
{   
    return d_verbose;
}

inline bool Options::daemon()
{   
    return not d_arg.option(0, "no-daemon");
}

inline bool Options::syslog() const
{   
    return d_useSyslog;
}

inline Options::Time Options::time() const
{   
    return d_time;
}

inline std::string const &Options::syslogTag() const
{   
    return d_syslogTag;
}

inline FBB::Priority Options::syslogPriority() const
{   
    return d_syslogPriority->second;
}

inline std::string const &Options::priority() const
{   
    return d_syslogPriority->first;
}

inline FBB::Facility Options::syslogFacility() const
{   
    return d_syslogFacility->second;
}

inline char const *Options::defaultConfigPath() 
{
    return s_defaultConfigPath;
}

inline std::string const &Options::facility() const
{   
    return d_syslogFacility->first;
}

inline std::string const &Options::conntrackPath() const
{
    return d_conntrackPath;
}


inline char const *Options::defaultConntrackPath() 
{
    return s_defaultConntrackPath;
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

#endif






