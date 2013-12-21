#include "conntrack.ih"

// Example conntrack lines: 

// [1338987414.52626 ]      [NEW] tcp      6 120 SYN_SENT 
//      src=192.168.1.4     dst=129.125.14.80   sport=59783 dport=22  [UNREPLIED] 
//      src=129.125.14.80   dst=129.125.100.246 sport=22    dport=59783

// [1387190223.487711]      [DESTROY] tcp  6                
//      src=192.168.17.21   dst=192.87.23.111   sport=50029 dport=443
//      src=192.87.23.111   dst=129.125.100.246 sport=443   dport=50029 [ASSURED] 

// [1387190207.172139]      [NEW] udp      17 30
//      src=10.4.0.6        dst=129.125.4.6       sport=42998 dport=53 [UNREPLIED]
//      src=129.125.4.6     dst=129.125.100.246   sport=53    dport=42998

// [1387190187.423829]      [DESTROY] udp      17
//      src=10.4.0.6        dst=216.239.34.10     sport=60840 dport=53
//      src=216.239.34.10   dst=129.125.100.246   sport=53    dport=60840

// [1387190207.153486]      [NEW] icmp 1 30             
//      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016 [UNREPLIED]  
//      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016 

// [1387190237.151720]      [DESTROY] icmp 1
//      src=192.168.17.7    dst=129.125.3.162     type=8 code=0 id=7016
//      src=129.125.3.162   dst=129.125.100.246   type=0 code=0 id=7016



void Conntrack::parentProcess()
{
//    Pattern pat(
//    //     1        2      3
//    "\\[(\\d+)\\.(\\d+).*(NEW|DESTROY).*"   // time: [1338899277.41469 ]
//    //      4             5
//    "src=(\\S+)\\s+dst=(\\S+)\\s+"          // source to nat,  dest
//    //        6               7
//    "sport=(\\d+)\\s+dport=(\\d+).*"        // source from,    dest port
//    //      8               
//    "dst=(\\S+).*"                          // natted source 
//    //        9
//    "dport=(\\d+)");                        // natted sport

    // [1338987414.52626 ]         [NEW] tcp      6 120 SYN_SENT 
    //      src=192.168.1.4 dst=129.125.14.80     sport=59783 dport=22  [UNREPLIED] 
    //      src=129.125.14.80 dst=129.125.100.246 sport=22 dport=59783
    Pattern tcpudp(
      //   1      2          3                 4  
    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+(tcp|udp).*)"    // time: [1338899277.41469 ]
      //     5           6
    R"(src=(\S+)\s+dst=(\S+)\s+)"           // source to nat,  dest
      //       7             8
    R"(sport=(\d+)\s+dport=(\d+).*)"        // source from,    dest port
      //      9               
    R"(dst=(\S+).*)"                        // natted source (key)
      //       10
    R"(dport=(\d+))",                       // natted sport  (key)
        true, 11);


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
            processed = tcpudpConnection(tcpudp);
        else if (icmp << line)
            processed = icmpConnection(icmp);

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





