#include <iostream>
#include <string>

//  See also: http://www.tenouk.com/Module43.html

#include <pcap.h>

#include <bobcat/inetaddress>
#include <bobcat/exception>

#include "pcappacket/pcappacket.h"

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


size_t port;

string nl{ "\n      " };

void tcpPacket(PcapPacket const &packet, 
                PcapPacket::Address const &src,
                PcapPacket::Address const &dst)
{
    PcapPacket::TCP_Flags flags = packet.flags();

            // starting a connection. FIN-ACK closes, after which the
            // other size normally sends another ACK.
    bool open = (flags == (PcapPacket::SYN | PcapPacket::ACK));

    string what = 
            open                                         ? "OPEN"   :
            flags == (PcapPacket::FIN | PcapPacket::ACK) ? "CLOSE"  :
            flags == PcapPacket::ACK ?                     "ACK"    :
                                                           "DATA";

    if (port == 0 || src.port() == port || dst.port() == port)
        cout << "TCP:  " <<
            packet.seconds() << ':' << packet.microSeconds() << ' ' <<
            src.dottedDecimalAddress() << " (" << src.port() << "), " <<
            dst.dottedDecimalAddress() << " (" << dst.port() << "): " <<
            "Flags: " << hex << "0x" << packet.flags() << dec << " (" <<
                                                        what << ')' << nl <<
            "Seq nr: " << packet.sequenceNr() << nl <<
            "IP Length: " << packet.ipLength() << ", "  
            "Data Length: " << packet.payloadLength() << nl <<
            "Data Offset: " << hex << packet.dataOffset() << dec << "\n"
        "\n";
}

void callback(u_char *user, struct pcap_pkthdr const *hdr,
              u_char const *bytes)
{
    PcapPacket packet(*hdr, bytes);

    PcapPacket::Address const &src = packet.sourceIP();
    PcapPacket::Address const &dst = packet.destIP();

    switch (packet.protocol())
    {
        case PcapPacket::ICMP:
            cout << "ICMP: " <<
                packet.seconds() << ':' << packet.microSeconds() << ' ' <<
                src.dottedDecimalAddress() << ", " <<
                dst.dottedDecimalAddress() << "): " << nl <<
                "IP Length: " << packet.ipLength() << ", "
                        "hdr length: " << packet.headerLength() << 
                        "payload length: " << packet.payloadLength() << "\n"  
            "\n";
        break;

        case PcapPacket::TCP:
            tcpPacket(packet, src, dst);
        break;

        case PcapPacket::UDP:
            cout << "UDP:  " <<
                packet.seconds() << ':' << packet.microSeconds() << ' ' <<
                src.dottedDecimalAddress() << " (" << src.port() << "), " <<
                dst.dottedDecimalAddress() << " (" << dst.port() << ')' << 
                                                                        nl <<
                "IP Length: " << packet.ipLength() << ", "
                                "udp length: " << packet.udpLength() << "\n"  
            "\n";
        break;

        default:
            cout << "  ?? " << packet.protocol() << " ??\n";
        break;
    };
}

int main(int argc, char **argv)
try
{
// prepare d_pcap
// ==============

    if (argc == 1)
        throw Exception() << "1st argument: device to inspect\n" 
                            "2nd argument (optional): tcp port to inspect";

    char const *device = argv[1];
    if (argc > 2)
        port = stoul(argv[2]);

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

// compile the filter expression
// =============================

    struct bpf_program d_pcapFilter;    

//    char filterExpr[] = "icmp or udp";
//    char filterExpr[] = "tcp";

    char filterExpr[] = "tcp or udp or icmp";

//        // "(tcp[13] & 0x10) != 0";
//        "( tcp[13] == 0x12"           // SYN,ACK
//        " or "
//        "tcp[13] == 0x11"             // FIN,ACK
//        " or "
//        "tcp[13] == 0x10 )";          // ACK

    if (pcap_compile(d_pcap, &d_pcapFilter, 
                     filterExpr, true, //optimize 
                     d_net) == -1) 
        throw Exception() << "Pcap compilation of `" << filterExpr << 
                            "' failed: " << pcap_geterr(d_pcap);

    if (pcap_setfilter(d_pcap, &d_pcapFilter) == -1) 
         throw Exception() << "Couldn't install filter `" << 
                filterExpr << ": " << pcap_geterr(d_pcap);

// retrieve packets
// ================

    u_char user[] = "";

    pcap_loop(d_pcap, -1, callback, user);
}
catch (exception const &exc)
{
    cerr << exc.what() << '\n';
}


