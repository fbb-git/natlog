#include "pcap.ih"

void Pcap::loop()
{
    cerr << "Starting the loop\n";

    pcap_loop(d_pcap, -1, callback, reinterpret_cast<u_char *>(this));
}
