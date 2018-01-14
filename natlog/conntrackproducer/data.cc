#include "conntrackproducer.ih"

    // [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
    //      src=192.168.1.4 dst=129.125.14.80     sport=59783 dport=22
    //                                                          [UNREPLIED] 
    //      packets=7 bytes=450 
    //      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783
    //      packets=7 bytes=450 ....

Pattern ConntrackProducer::s_tcpudp
{
    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+(tcp|udp).*)"
      //   1      2          3                 4    time: [1338899277.41469 ]

    R"(src=(\S+)\s+dst=(\S+)\s+)"               // source to nat,  dest
      //     5           6

    R"(sport=(\d+)\s+dport=(\d+))"              // source from,    dest port
      //       7             8

    R"((\s+packets=(\d+)\s+bytes=(\d+))?.*)"    // maybe sent packets/bytes
      //9           10            11

    R"(dst=(\S+).*)"                            // natted source (key)
      //     12 (was: 9)

    R"(dport=(\d+))"                            // natted dport  (key)
      //      13 (was: 10)

    R"((\s+packets=(\d+)\s+bytes=(\d+))?)",     // maybe recv'd packets/bytes
      //14          15            16

    true, static_cast<size_t>(CTtcpudp::nFields) 
};
//  If packets/bytes are not provided then the final #14 thru #16 are not
//  available, and end() returns 14, otherwise 17.



///////////////////////////////////////////////////////////////////////////

    // [1387190207.153486]      [NEW] icmp 1 30             
    //      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016
    //                                                          [UNREPLIED]
    //      packets=1 bytes=84      <-- maybe
    //      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016 
    //      packets=1 bytes=84      <-- maybe

Pattern ConntrackProducer::s_icmp
{
      // [1514579857.235298]	[DESTROY] icmp     1 

    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+icmp.*)"
      //   1      2       3              

    //src=192.168.17.6 dst=129.125.3.162
    R"(src=(\S+)\s+dst=(\S+)\s+)"               // source to nat,  dest
    //      4           5    

    // type=8 code=0 id=3269 
    R"(\S+\s+\S+\s+id=(\d+)\s+)"                // id= (key)
    //                  6    

    // packets=4 bytes=336 
    R"((packets=(\d+)\s+bytes=(\d+)\s+)?)"      // maybe sent packets/bytes
    // 7          8             9      

    // src=129.125.3.162 dst=192.168.8.17 type=0 code=0 id=3269 
    R"(.*dst=(\S+).*id=\d+)"                    // natted source
    //        10 (was: 7)      

    // packets=4 bytes=336
    R"((\s+packets=(\d+)\s+bytes=(\d+))?)",     // maybe rev'd packets/bytes
    //  11          12            13

        true, static_cast<size_t>(CTicmp::nFields) 
};
//  If packets/bytes are not provided then the final #11 thru #13 are not
//  available, and end() returns 11, otherwise 14.


