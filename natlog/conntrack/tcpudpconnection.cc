#include "conntrack.ih"

// See below and parentprocess.cc for the pattern-organization 

bool Conntrack::tcpudpConnection(Pattern const &tcpudp)
{
    string key(
                tcpudp[ idx(CTtcpudp::NATSRC) ]  + 
                tcpudp[ idx(CTtcpudp::NATPORT) ] 
            );

    if (tcpudp[ idx(CTtcpudp::TYPE) ] == "NEW")
        d_connections.addTcpudp(key, tcpudp);
    else 
    {
        size_t findIdx = d_connections.find(key);
        if (findIdx == numeric_limits<size_t>::max())   // no record (yet)
            return false;

        logTcpudp(
            *d_connections[findIdx], tcpudp[ idx(CTtcpudp::TIME1) ],
                                 tcpudp[ idx(CTtcpudp::TIME2) ]
        ); 

        d_connections.erase(findIdx);  // erase processed element
    }
    return true;
}


// // [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
// //      src=192.168.1.4 dst=129.125.14.80     sport=59783 dport=22
// //                                                          [UNREPLIED] 
// //      packets=7 bytes=450 
// //      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783
// //      packets=7 bytes=450 ....
// Pattern tcpudp{
//   //   1      2          3                 4    time: [1338899277.41469 ]
// R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+(tcp|udp).*)"
//   //     5           6
// R"(src=(\S+)\s+dst=(\S+)\s+)"               // source to nat,  dest
//   //       7             8
// R"(sport=(\d+)\s+dport=(\d+))"              // source from,    dest port
//   //9           10            11
// R"((\s+packets=(\d+)\s+bytes=(\d+))?.*)"    // maybe sent packets/bytes
//   //     12 (was: 9)
// R"(dst=(\S+).*)"                            // natted source (key)
//   //      13 (was: 10)
// R"(dport=(\d+))"                            // natted dport  (key)
//   //14          15            16
// R"((\s+packets=(\d+)\s+bytes=(\d+))?)",     // maybe recv'd packets/bytes
//
// true, idx(CTtcpudp::nFields) };
// 
// //  If packets/bytes are not provided then #14 t/m #16 are not available,
// //  and end() does not return CTtcpudp::nFields (but 3 less).
