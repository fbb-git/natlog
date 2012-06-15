#include "pcap.ih"

Pcap::Pcap(char const *device, bool promisc, size_t snapLen, size_t timeOutMs)
{
    // see the posting by user175104 on 
    // http://stackoverflow.com/questions/1779715/
    //              how-to-get-mac-address-of-your-machine-using-a-c-program 

    ifstream mac((string("/sys/class/net/") + device) + "/address");

    string address;
    mac >> address;

    cout << "MAC address: `" << address << "'\n";

    d_shift = mac ? 0 : PcapPacket::SIZEOF_ETHERNET_HEADER;

    cout << "SHIFT = " << d_shift << endl;

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
