#include "conntrack.ih"

// Example conntrack lines: 
// The 'maybe' entries appear if the command
//  
//      $ echo 1 > /proc/sys//net/netfilter/nf_conntrack_acct
//
//  has been issued before starting natlog.

// [1338987414.52626 ]      [NEW] tcp      6 120 SYN_SENT 
//      src=192.168.1.4     dst=129.125.14.80   sport=59783 dport=22  [UNREPLIED] 
//      src=129.125.14.80   dst=129.125.100.246 sport=22    dport=59783

// [1387190223.487711]      [DESTROY] tcp  6                
//      src=192.168.17.21   dst=192.87.23.111   sport=50029 dport=443
//      packets=7 bytes=450     <-- maybe
//      src=192.87.23.111   dst=129.125.100.246 sport=443   dport=50029 
//      packets=5 bytes=1679    <-- maybe
//      [ASSURED] 



// [1387190207.172139]      [NEW] udp      17 30
//      src=10.4.0.6        dst=129.125.4.6       sport=42998 dport=53 [UNREPLIED]
//      src=129.125.4.6     dst=129.125.100.246   sport=53    dport=42998

// [1387190187.423829]      [DESTROY] udp      17
//      src=10.4.0.6        dst=216.239.34.10     sport=60840 dport=53
//      packets=1 bytes=138     <-- maybe
//      src=216.239.34.10   dst=129.125.100.246   sport=53    dport=60840
//      packets=1 bytes=524     <-- maybe


//  Note that the tcp and udp lines are organized identically


// [1387190207.153486]      [NEW] icmp 1 30             
//      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016 [UNREPLIED]  
//      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016 

// [1387190237.151720]      [DESTROY] icmp 1
//      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016
//      packets=1 bytes=84      <-- maybe
//      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016
//      packets=1 bytes=84      <-- maybe



void Conntrack::parentProcess()
{
    // [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
    //      src=192.168.1.4 dst=129.125.14.80     sport=59783 dport=22  [UNREPLIED] 
    //      packets=7 bytes=450 
    //      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783
    //      packets=7 bytes=450 ....
    Pattern tcpudp(
      //   1      2          3                 4  
    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+(tcp|udp).*)"    // time: [1338899277.41469 ]
      //     5           6
    R"(src=(\S+)\s+dst=(\S+)\s+)"               // source to nat,  dest
      //       7             8
    R"(sport=(\d+)\s+dport=(\d+))"              // source from,    dest port
      //9           10            11
    R"((\s+packets=(\d+)\s+bytes=(\d+))?.*)"    // maybe sent packets/bytes
      //     12 (was: 9)
    R"(dst=(\S+).*)"                            // natted source (key)
      //      13 (was: 10)
    R"(dport=(\d+))"                            // natted dport  (key)
      //14          15            16
    R"((\s+packets=(\d+)\s+bytes=(\d+))?)",     // maybe recv'd packets/bytes
        true, 17);

    //  If packets/bytes are not provided then #14 t/m #16 are not available,
    //  and end() returns 14, otherwise 17.

    // [1387190207.153486]      [NEW] icmp 1 30             
    //      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016 [UNREPLIED]  
    //      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016 
    Pattern icmp(
      //   1      2          3                   
    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+icmp.*)"    // time: [1338899277.41469 ]
      //     4           5
    R"(src=(\S+)\s+dst=(\S+)\s+)"           // source to nat,  dest
      //    6    
    R"(.*(id=\d+).*)"                       // id= (key)
      //     7               
    R"(dst=(\S+).*)",                       // natted source
        true, 11);


    string line;
    while (getline(cin, line))
    {
        imsg << "LINE: " << line << endl;

        bool processed = true;

        if (tcpudp << line)
        {
            if (not accept(tcpudp[4]))      // observed protocol must
                continue;                   // match accepted protocol
            processed = tcpudpConnection(tcpudp);
        }
        else if (icmp << line)
        {
            if (not accept(tcpudp[4]))
                continue;
            processed = icmpConnection(icmp);
        }

        if (not processed)
            wmsg << "UNAVAILABLE: " << line << endl;
    }

    waitForChild();

    if (not d_stop)
    {
        cin.clear();
        throw Options::CONNTRACK_ENDED;
    }
}





