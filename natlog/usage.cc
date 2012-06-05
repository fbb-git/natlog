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
    "                           (default: `" << g_config << "'\n"
    "      --conntrack 'cmd'  - cmd: conntrack command to execute\n"
    "      --daemon (-d)      - run " << progname << " in the background\n"
    "      --help (-h)        - provide this help\n"
    "      --version (-v)     - show version information and terminate\n"
    "   command   - command to execute:\n"
    "       conntrack:  use `conntrack' to find the source-nat connections\n"
    "\n";
}
