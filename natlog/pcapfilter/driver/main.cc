#include <iostream>
#include <string>

//  See also: http://www.tenouk.com/Module43.html

#include <pcap.h>

#include <bobcat/inetaddress>
#include <bobcat/exception>

#include "pcaprecord/pcaprecord.h"

// see also ../pcap/callback.demo

using namespace std;
using namespace FBB;


// ICMP
// 10:58:59.176351 IP ballistix.oostum.north > suffix.rc.rug.nl: ICMP echo
//                                          request, id 5589, seq 1, length 64
// 10:58:59.205235 IP suffix.rc.rug.nl > ballistix.oostum.north: ICMP echo
//                                          reply, id 5589, seq 1, length 64 
// The length can be computed by subtracting the IP header length (20) from
//  the IP header's length field (cf. pcappacket.h)

// UDP
// 11:02:38.095099 IP 192.168.17.6.123 > 213.75.85.245.123: NTPv4, Client, 
//                                          length 48


size_t g_port;

string nl{ "\n      " };

void tcpPacket(Record const &packet)
{
    size_t flags = packet.flags();

            // starting a connection. FIN-ACK closes, after which the
            // other size normally sends another ACK.
    bool open = (flags == (Record::SYN | Record::ACK));

    string what = 
            open                                         ? "OPEN"   :
            flags == (Record::FIN | Record::ACK) ? "CLOSE"  :
            flags == Record::ACK ?                     "ACK"    :
                                                           "DATA";

    if (
        g_port == 0 || packet.sourcePort() == g_port || 
                       packet.destPort() == g_port
    )
        cout << "TCP:  " <<
            packet.seconds() << ':' << packet.muSeconds() << ' ' <<

            packet.sourceIP() << " (" << packet.sourcePort() << "), " <<
            packet.destIP() << " (" << packet.destPort() << "), " << nl <<

            "Key: " << packet.key() << ", "
            "Flags: " << hex << "0x" << flags << dec << " (" <<
                                                        what << "), " << 
            "payload length: " << packet.payload() <<  dec << "\n"
        "\n";
}

void callback([[maybe_unused]] u_char *user, struct pcap_pkthdr const *hdr,
              u_char const *bytes)
{
    PcapRecord packet{PcapRecord::IN,  *hdr, bytes };

    switch (packet.protocol())
    {
        case Record::ICMP:
            cout << "ICMP: " <<
                packet.seconds() << ':' << packet.muSeconds() << ' ' <<
                packet.sourceIP() << ", " <<
                packet.destIP() << "): " << nl <<
                "ID: " << packet.id() << ", " << packet.key() << ", "
                        "payload length: " << packet.payload() << "\n"  
            "\n";
        break;

        case Record::TCP:
            tcpPacket(packet);
        break;

        case Record::UDP:
            cout << "UDP:  " <<
                packet.seconds() << ':' << packet.muSeconds() << ' ' <<
                packet.sourceIP() << " (" << packet.sourcePort() << "), " <<
                packet.destIP() << " (" << packet.destPort() << "), " <<
                                                                        nl <<
                "Key: " << packet.key() << ", "
                            "payload length: " << packet.payload() << "\n"  
                                            // udpLength
            "\n";
        break;

        default:
            cout << "  ?? " << packet.protocol() << " ??\n";
        break;
    }
}

int main(int argc, char **argv)
try
{
// prepare d_pcap
// ==============

    if (argc == 1)
        throw Exception() << "1st argument: device to inspect\n" 
                            "2nd argument: tcp, icmp, udp or all\n"
                            "3nd argument (optional): tcp port to inspect";

    char const *device = argv[1];
    if (argc > 3)
        g_port = stoul(argv[3]);

    char errBuf[PCAP_ERRBUF_SIZE];      // pcap-predefined constant

    pcap_t *d_pcap =    //      snaplen   promisc   timeOutMs
         pcap_open_live(device, 1500,     false,    1000,       errBuf);

    if (d_pcap == 0)
        throw Exception() << errBuf;

    bpf_u_int32 netMask;        // The netmask of our sniffing device

    bpf_u_int32 d_net;

    if (pcap_lookupnet(device, &d_net, &netMask, errBuf) == -1) 
        throw Exception() << 
                "Can't get network address of device " << device;

// compile the filter expression, see pcapfilter/pcapfilter1.cc and
//                                    pcap/pcap1.cc 
// =============================

    struct bpf_program d_pcapFilter;    

    string filterExpr{ argv[2] };
    if (filterExpr == "all")
        filterExpr = "icmp or udp or tcp";

    if (pcap_compile(d_pcap, &d_pcapFilter, 
                     filterExpr.c_str(), true, //optimize 
                     d_net) == -1) 
        throw Exception() << "Pcap compilation of `" << filterExpr << 
                            "' failed: " << pcap_geterr(d_pcap);

    if (pcap_setfilter(d_pcap, &d_pcapFilter) == -1) 
         throw Exception() << "Couldn't install filter `" << 
                filterExpr << ": " << pcap_geterr(d_pcap);

// receive and handle packets
// ==========================

    pcap_loop(d_pcap, -1, callback, 0);
}
catch (exception const &exc)
{
    cerr << exc.what() << '\n';
}




