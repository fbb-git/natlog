//                     usage.cc

#include "main.ih"

void usage(std::string const &progname)
{
    cout << "\n" <<
    "Usage: " << progname << " [options] args\n"
    "Where:\n"
    "   [options] - optional arguments (short options between parentheses):\n"
    "      --help (-h)      - provide this help\n"
    "      --version (-v)   - show version information and terminate\n"
    "   args   - explain additional arguments.\n"
    "\n";
}
