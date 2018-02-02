//                     usage.cc

#include "main.ih"

void usage(std::string const &progname)
{
    cout << "\n" <<
    "Usage: " << progname << " args\n"
    "Where:\n"
    "   1st arg: device to capture\n"
    "   other args: pcap-filter expression\n"
    "\n";
}
