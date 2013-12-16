#include "conntrack.ih"

//    // [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
//    //      src=192.168.1.4 dst=129.125.14.80     sport=59783 dport=22  [UNREPLIED] 
//    //      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783
//    Pattern tcpudp(
//      //   1      2          3                 4  
//    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+(tcp|udp).*)"    // time: [1338899277.41469 ]
//      //     5           6
//    R"(src=(\S+)\s+dst=(\S+)\s+)"           // source to nat,  dest
//      //       7             8
//    R"(sport=(\d+)\s+dport=(\d+).*)"        // source from,    dest port
//      //      9               
//    R"(dst=(\S+).*)"                        // natted source (key)
//      //       10
//    R"(dport=(\d+))");                      // natted sport  (key)

bool Conntrack::tcpudpConnection(Pattern const &tcpudp)
{
    string key(tcpudp[9] + tcpudp[10]);

    if (tcpudp[3] == "NEW")
        d_connections.addTcpudp(key, tcpudp);
    else 
    {
        size_t idx = d_connections.find(key);
        if (idx == numeric_limits<size_t>::max())
            return false;

        logTcpudp(*d_connections[idx], tcpudp[1], tcpudp[2]);
        d_connections.erase(idx);  // erase processed element
    }
    return true;
}

