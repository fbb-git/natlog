#include "pcap.ih"

Pcap::Pcap(char const *device, bool promisc, size_t snapLen, size_t timeOutMs)
:
    d_errBuf(new char[PCAP_ERRBUF_SIZE]),
    d_pcap(pcap_open_live(device, snapLen, promisc, timeOutMs, 
                          d_errBuf.get()))
{
    if (d_pcap == 0)
        fmsg << d_errBuf.get() << endl;
}
