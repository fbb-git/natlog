#include "main.ih"
#include <limits>

// note: tcpdump only reads files when tcpdump is started by the user
// owning those files.

#include <iomanip>

/*
    typedef int bpf_int32;
    typedef u_int bpf_u_int32;

    struct pcap_file_header {
        bpf_u_int32 magic;
        u_short version_major;
        u_short version_minor;
        bpf_int32 thiszone;     // gmt to local correction
        bpf_u_int32 sigfigs;    // accuracy of timestamps
        bpf_u_int32 snaplen;    // max length saved portion of each pkt
        bpf_u_int32 linktype;   // data link type (LINKTYPE_*)
    };

    struct pcap_pkthdr {
        struct timeval ts;      // time stamp
        bpf_u_int32 caplen;     // length of portion present
        bpf_u_int32 len;        // length this packet (off wire)
    };

*/

struct pkthdr {
    uint32_t     seconds;     // time stamp
    uint32_t     muSeconds;   // time stamp

    bpf_u_int32 caplen;     // length of portion present
    bpf_u_int32 len;        // length this packet (off wire)
};


size_t g_count1 = 0;
size_t g_count2 = 0;

size_t get(istream &in, pkthdr &hdr)
{
    in.read(reinterpret_cast<char *>(&hdr), sizeof(pkthdr));
    
    return in.good() ? 
                        static_cast<size_t>(hdr.seconds) 
                    : 
                        numeric_limits<size_t>::max();
}

size_t curLen = 0;
char *g_data = 0;

size_t process(ostream &out, istream &in, pkthdr &hdr)
{
    out.write(reinterpret_cast<char *>(&hdr), sizeof(pkthdr));
    size_t length = hdr.len;        // ip header length already in host
                                    // byte order.
    if (length > curLen)
    {
        delete[] g_data;
        g_data = new char[length];
        curLen = length;
    }
    in.read(g_data, length);
    out.write(g_data, length);
    return get(in, hdr);
}
    
int main(int argc, char **argv)
try
{
    if (argc == 1)
    {
        cout << 
            "option: -h: write tcpdump1's global header to the merged file\n"
            "arguments: tcpdump1 file, tcpdump2 file, merged file\n";
        return 0;
    }

    bool writeHdr = false;

    if (argv[1] == "-h"s)
    {
        writeHdr = true;
        ++argv;
    }

    ifstream in1(argv[1]);
    ifstream in2(argv[2]);
    ofstream out(argv[3]);

    struct Ethernet_Header      // http://en.wikipedia.org/wiki/EtherType
    {
        u_char destMac[6];      // Destination host MAC address
        u_char srcMac[6];       // Source host MAC address
        u_short ether_type;     // IP? ARP? RARP? etc 
    };

    if (not writeHdr)
        in1.ignore(24);             // skip the global headers
    else
    {
        g_data = new char[24];
        curLen = 24;
        in1.read(g_data, 24);
        out.write(g_data, 24);
    }

    in2.ignore(24);

    pkthdr hdr1;
    pkthdr hdr2;
    

    size_t seconds1 = get(in1, hdr1);
    size_t seconds2 = get(in2, hdr2);

    while 
    (
        seconds1 != numeric_limits<size_t>::max()
        &&
        seconds1 != numeric_limits<size_t>::max()
    )
    {
        if (seconds1 < seconds2)
        {
            ++g_count1;
            seconds1 = process(out, in1, hdr1);
        }
        else if (seconds1 > seconds2)
        {
            ++g_count2;
            seconds2 = process(out, in2, hdr2);
        }
        else
        {
            ++g_count1;
            seconds1 = process(out, in1, hdr1);

            ++g_count2;
            seconds2 = process(out, in2, hdr2);
        }
    }
        
    cout << "Wrote " << g_count1 << " records from the 1st file\n"
            "wrote " << g_count2 << " records from the 2nd file\n";

}
catch (...)
{
}





