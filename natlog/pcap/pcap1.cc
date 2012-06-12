#include "pcap.ih"

Pcap::Pcap(char const *device, bool promisc, size_t snapLen, size_t timeOutMs)
{
    char errBuf[PCAP_ERRBUF_SIZE];

    d_pcap = pcap_open_live(device, snapLen, promisc, timeOutMs, errBuf);

    if (d_pcap == 0)
        fmsg << errBuf << endl;

    bpf_u_int32 netMask;        // The netmask of our sniffing device

    if (pcap_lookupnet(device, &d_IP, &netMask, errBuf) == -1) 
    {
        emsg << "Can't get netmask for device " << device << endl;
        d_IP = 0;
    }
}
