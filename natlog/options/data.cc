#include "options.ih"

char const Options::s_defaultConfigPath[]       = "/etc/natlog.conf";

char const Options::s_defaultConntrackCommand[] = "/usr/sbin/conntrack";
char const Options::s_defaultConntrackDevice[]  = "/proc/net/nf_conntrack";
char const Options::s_defaultConntrackArgs[]    = 
                                        " -E -n -o timestamp -e NEW,DESTROY";

char const Options::s_defaultSyslogIdent[]      = "NATLOG";
char const Options::s_defaultSyslogFacility[]   = "DAEMON";
char const Options::s_defaultSyslogPriority[]   = "NOTICE";
char const Options::s_defaultPIDfile[]          = "/run/natlog.pid";

unordered_map<string, Options::Time> const Options::s_time = 
    {
        {"raw",     RAW},
        {"utc",     UTC},
        {"local",   LT},
    };


unordered_map<string, Facility> const Options::s_syslogFacilities = 
    {
        {"DAEMON", Facility::DAEMON}, 
        {"LOCAL0", Facility::LOCAL0},
        {"LOCAL1", Facility::LOCAL1},
        {"LOCAL2", Facility::LOCAL2},
        {"LOCAL3", Facility::LOCAL3},
        {"LOCAL4", Facility::LOCAL4},
        {"LOCAL5", Facility::LOCAL5},
        {"LOCAL6", Facility::LOCAL6},
        {"LOCAL7", Facility::LOCAL7},
        {"USER",   Facility::USER}
    };

unordered_map<string, Priority> const Options::s_syslogPriorities = 
    {
       {"EMERG",    Priority::EMERG},
       {"ALERT",    Priority::ALERT},
       {"CRIT",     Priority::CRIT},
       {"ERR",      Priority::ERR},
       {"WARNING",  Priority::WARNING},
       {"NOTICE",   Priority::NOTICE},
       {"INFO",     Priority::INFO},
       {"DEBUG",    Priority::DEBUG}
    };

unordered_map<string, IP_Types::Protocol> const Options::s_name2protocol = 
    {
        { "icmp",   IP_Types::ICMP },
        { "tcp",    IP_Types::TCP },
        { "udp",    IP_Types::UDP },
    };

unordered_map<IP_Types::Protocol, string> const Options::s_protocol2name = 
    {
        { IP_Types::ICMP,   "icmp" },
        { IP_Types::TCP,    "tcp"  },
        { IP_Types::UDP,    "udp"  },
    };

Options *Options::s_options = 0;
