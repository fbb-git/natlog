//                     usage.cc

#include "main.ih"

void usage(std::string const &progname)
{
    cout << "\n" <<
    progname << " by " << Icmbuild::author << "\n" <<
    progname << " V" << Icmbuild::version << " " << Icmbuild::years << "\n"
    "\n"
    "Usage: " << progname << " [options] command\n"
    "Where:\n"
    "   [options] - optional arguments (short options between parentheses):\n"
    "      --config (-c) path - path: pathname of the configuation file\n"
    "                           (default: `" << 
                                Options::defaultConfigPath() << "')\n"
    "      --conntrack path   - path: path to the `conntrack' program\n"
    "                           (default `" << 
                                Options::defaultConntrackPath() << "')\n"
    "      --no-daemon        - do not run " << progname << 
                                                        " in the background\n"
    "      --help (-h)        - provide this help\n"
    "      --no-syslog        - do not write syslog messages\n"
    "      --syslog-tag id  - id: identifier prefixed to syslog messages\n"
    "                           (default `" << 
                                Options::defaultSyslogIdent() << "')\n"
    "      --syslog-facility fac  - fac: syslog facility to use\n"
    "                           (default `" << 
                                Options::defaultSyslogFacility() << "')\n"
    "      --syslog-priority pri  - pri: syslog priority to use\n"
    "                           (default `" << 
                                Options::defaultSyslogPriority() << "')\n"
    "      --time (-t) spec   - time specification:\n"
                                "raw: (default) seconds since the epoch;\n"
                                "utc: date and time in UTC\n"
                                "local: local date and time\n"
    "      --verbose          - write additional information to stdout\n"
    "      --version (-v)     - show version information and terminate\n"
    "   command   - command to execute:\n"
    "       conntrack:  use `conntrack' to find the source-nat connections\n"
    "\n";
}
