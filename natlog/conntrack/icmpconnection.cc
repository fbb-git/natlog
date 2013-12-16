#include "conntrack.ih"

//    // [1387190207.153486]      [NEW] icmp 1 30           
//    //      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016 [UNREPLIED]  
//    //      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016 
//    Pattern icmp(
//      //   1      2          3                   
//    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+icmp.*)"    // time: [1338899277.41469 ]
//      //     4           5
//    R"(src=(\S+)\s+dst=(\S+)\s+)"           // source to nat,  dest
//      //    6    
//    R"(.*(id=\d+).*)"                       // id= (key)
//      //     7               
//    R"(dst=(\S+).*)");                      // natted source

bool Conntrack::icmpConnection(Pattern const &icmp)
{
    if (icmp[3] == "NEW")
        d_connections.addIcmp(icmp[6], icmp);
    else 
    {
        size_t idx = d_connections.find(icmp[6]);
        if (idx == numeric_limits<size_t>::max())
            return false;

        logIcmp(*d_connections[idx], icmp[1], icmp[2]);
        d_connections.erase(idx);  // erase processed element
    }
    return true;
}

