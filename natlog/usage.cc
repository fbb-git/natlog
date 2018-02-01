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
"      --conntrack-command cmd - cmd: `conntrack' program location\n"
"                           (default `" << 
                                Options::defaultConntrackCommand() << "')\n"
"      --conntrack-device dev - dev: `conntrack' data device\n"
"                           (default `" << 
                                Options::defaultConntrackDevice() << "')\n"
"      --conntrack-ip-header-size size - size: assumed IP header sizes\n"
"                           (default: 0, commonly encountered: 20)\n"
"      --conntrack-restart max - max number of times `conntrack' is\n"
"                           restarted if prematurely ended\n"
"                           (default 10 restarts)\n"
"      --help (-h)        - provide this help\n"
"      --log-data path    - write log-data on the file `path'\n"
"      --no-daemon        - do not run " << progname << " in the background\n"
"      --no-syslog        - do not write syslog messages\n"
"      --pid-file (-p) path - `path' is the name of the file holding the\n"
"                           daemon's PID\n"
"                           (default `" <<
                                Options::defaultPIDfile() << "')\n"
"      --protocol (-P) spec - spec: protocols handled by " << 
                                                        progname << "\n"
"                           command. Use colon separated combinations of\n"
"                           tcp (default), udp and icmp, or use `all'\n"
"      --stdout (-s)      - write syslog-equivalent messages to the std "
                                                                    "output\n"
"      --syslog-tag id    - id: identifier prefixed to syslog messages\n"
"                           (default `" << 
                                Options::defaultSyslogIdent() << "')\n"
"      --syslog-facility fac  - fac: syslog facility to use\n"
"                           (default `" << 
                                Options::defaultSyslogFacility() << "')\n"
"      --syslog-priority pri  - pri: syslog priority to use\n"
"                           (default `" << 
                                Options::defaultSyslogPriority() << "')\n"
"                            (implied by --verbose; only for --no-daemon)\n"
"      --terminate        - end a running natlog program using the PID "
                                                                    "found\n"
"                           in the PID-file (see option --pid-file)\n"
"      --time (-t) spec   - time specification:\n"
"                               raw:   (default) seconds since the epoch;\n"
"                               utc:   date and time in UTC\n"
"                               local: local date and time\n"
"      --ttl (-T) secs    - time-to-live for received ICMP/UDP connections:\n"
"                           info about connections is logged if they are "
                                                                    "not\n"
"                           used for `secs' seconds (default: " << 
                                                Options::TTL << " seconds).\n"
"      --verbose (-V)     - write additional information:\n"
"                               with --no-daemon: to stdout;\n"
"                               with daemons and --no-syslog not "
                                                                "specified:\n"
"                                                 to the syslog daemon\n"
"      --version (-v)     - show version information and terminate\n"
// "      --warn (-w)        - warn about not-registered connections\n"
"                            (suppressed by --no-daemon)\n"
"   command   - command to execute:\n"
"       conntrack:  use `conntrack' to find the source-nat connections\n"
"       in out:     in, out: names of network devices (e.g., eth0)\n"
"                   directly capture packets on the `in' and `out' "
                                                            "devices\n"
"                   in: source natting is applied to its source "
                                                            "addresses\n"
"                   out: the (natting) device connecting to the\n"
"                        destination addresses\n"
"       in inAddr inMask out outAddr outMask:\n"
"                   in, out: names of files written by tcpdump\n"
"                   (e.g., tcpdump -i device -w filename)\n"
"                   `in': in-device packages (source natting was applied to\n"
"                         `in')\n"
"                   `out' packages of the device connecting to the "
                                                            "destination\n" 
"                         addresses\n"  
"                   `inAddr inMask': address and netmask of the "
                                                            "in-device\n"
"                   `outAddr outMask': address and netmask of the "
                                                            "out-device\n";

}
