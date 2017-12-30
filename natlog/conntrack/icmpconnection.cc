#include "conntrack.ih"

// See below and parentprocess.cc for the pattern-organization 


bool Conntrack::icmpConnection(Pattern const &icmp)
{
    if (icmp[ idx(CTicmp::TYPE) ] == "NEW")
        d_connections.addIcmp(icmp[ idx(CTicmp::ID) ], icmp);
    else 
    {
        size_t findIdx = d_connections.find(icmp[ idx(CTicmp::ID) ]);
        if (findIdx == numeric_limits<size_t>::max())
            return false;

        logIcmp(
            *d_connections[findIdx], 
            icmp[ idx(CTicmp::TIME1) ], icmp[ idx(CTicmp::TIME2) ],
            icmp[ idx(CTicmp::SENTBYTES) ], icmp[ idx(CTicmp::RECVDBYTES) ]
        );

        d_connections.erase(findIdx);  // erase processed element
    }
    return true;
}


//  Pattern icmp{
//    // [1514579857.235298]	[DESTROY] icmp     1 
//  R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+icmp.*)"
//    //   1      2       3              
//
//  //src=192.168.17.6 dst=129.125.3.162
//  R"(src=(\S+)\s+dst=(\S+)\s+)"               // source to nat,  dest
//  //      4           5    
//
//  // type=8 code=0 id=3269 
//  R"(\S+\s+\S+\s+id=(\d+)\s+)"                // id= (key)
//  //                  6    
//
//  // packets=4 bytes=336 
//  R"((packets=(\d+)\s+bytes=(\d+)\s+)?)"      // maybe sent packets/bytes
//  // 7          8             9      
//
//  // src=129.125.3.162 dst=192.168.8.17 type=0 code=0 id=3269 
//  R"(.*dst=(\S+).*id=\d+)"                    // natted source
//  //        10 (was: 7)      
//
//  // packets=4 bytes=336
//  R"((\s+packets=(\d+)\s+bytes=(\d+))?)",     // maybe rev'd packets/bytes
//  //  11          12            13
//
//      true, idx(CTicmp::nFields) };
//
//
//  //  If packets/bytes are not provided then #7 t/m #9 are not available,
//  //  and end() does not return CTicmp::nFields (but 3 less).

