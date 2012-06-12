#include "pcap.ih"

void Pcap::loop(u_char *user, pcap_handler callback)
{
    pcap_loop(d_pcap, -1, callback, user);
}
