#include "pcap.ih"

void Pcap::computeShift(char const *device)
{
    // see the posting by user175104 on 
    // http://stackoverflow.com/questions/1779715/
    //              how-to-get-mac-address-of-your-machine-using-a-c-program 

    ifstream mac((string("/sys/class/net/") + device) + "/address");

    string address;
    d_shift = (mac >> address) ? 0 : PcapPacket::SIZEOF_ETHERNET_HEADER;

    if (d_shift == 0)
        imsg << "Device " << device << " has MAC address " << address << endl;
    else
        imsg << "Device " << device << " has no MAC address: packets lack "
                                    "Ethernet headers" << endl;
}
