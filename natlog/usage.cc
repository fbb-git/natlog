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
    "      --conntrack-command cmd - cmd: `conntrack' command specification\n"
    "                           (default `" << 
                                Options::defaultConntrackCommand() << "')\n"
    "      --conntrack-restart max - max number of times `conntrack' is\n"
    "                           restarted if prematurely ended\n"
    "                           (default 10 restarts)\n"
    "      --help (-h)        - provide this help\n"
    "      --no-daemon        - do not run " << progname << 
                                                        " in the background\n"
    "      --no-syslog        - do not write syslog messages\n"
    "      --pid-file (-p) path - `path' is the name of the file holding "
                                                                    "the\n"
    "                           daemon's PID\n"
    "                           (default `" <<
                                        Options::defaultPIDfile() << "')\n"
    "      --protocol spec    - spec: protocols handled with the `conntrack'\n"
    "                           comand. Use colon separated combinations of\n"
    "                           tcp, udp and icmp, or use `all' "
                                                            "(default: tcp)\n"
    "      --syslog-tag id    - id: identifier prefixed to syslog messages\n"
    "                           (default `" << 
                                Options::defaultSyslogIdent() << "')\n"
    "      --syslog-facility fac  - fac: syslog facility to use\n"
    "                           (default `" << 
                                Options::defaultSyslogFacility() << "')\n"
    "      --syslog-priority pri  - pri: syslog priority to use\n"
    "                           (default `" << 
                                Options::defaultSyslogPriority() << "')\n"
    "      --stdout (-s)      - write syslog-equivalent messages to the std "
                                                                "output\n"
    "                            (implied by --verbose; only for " 
                                                            "--no-daemon)\n"
    "      --time (-t) spec   - time specification:\n"
    "                            raw: (default) seconds since the epoch;\n"
    "                            utc: date and time in UTC\n"
    "                            local: local date and time\n"
    "      --verbose          - write additional information:\n"
    "                               with --no-daemon: to stdout;\n"
    "                               with daemons and --no-syslog not "
                                                                "specified:\n"
    "                                                 to the syslog daemon\n"
    "                            (only for --no-daemon)\n"
    "      --version (-v)     - show version information and terminate\n"
    "      --warn (-w)        - warn about not-registered connections\n"
    "                            (suppressed by --no-daemon)\n"
    "   command   - command to execute:\n"
    "       conntrack:  use `conntrack' to find the source-nat connections\n"
    "       in out:     in, out: names of network devices (e.g., eth0)\n"
    "                   directly capture packets on the `in' and `out' "
                                                                "devices\n"
    "                   in: soource natting is applied to its source "
                                                                "addresses\n"
    "                   out: the device connecting to the destination\n"
    "                        addresses\n"


    "\n";
}
