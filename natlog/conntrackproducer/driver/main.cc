#include <iostream>
#include <string>

#include <bobcat/pattern>

using namespace std;
using namespace FBB;

int main(int argc, char **argv)
{
    Pattern tcpudp{
      //   1      2          3                 4  time: [1338899277.41469 ]
    R"(\[(\d+)\.(\d+).*\[(NEW|DESTROY)\]\s+(tcp|udp).*)"    
      //     5           6
    R"(src=(\S+)\s+dst=(\S+)\s+)"               // source to nat,  dest
      //       7             8
    R"(sport=(\d+)\s+dport=(\d+))"              // source from,    dest port
      //9           10            11
    R"((\s+packets=(\d+)\s+bytes=(\d+))?.*)"    // maybe sent packets/bytes
      //     12 (was: 9)
    R"(dst=(\S+).*)"                            // natted source (key)
      //      13 (was: 10)
    R"(dport=(\d+))"                            // natted sport  (key)
      //14          15            16
    R"((\s+packets=(\d+)\s+bytes=(\d+))?)",     // maybe recv'd packets/bytes
        true, 17 };


    Pattern icmp{
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

        true, 14 };


    Pattern &pat = argc > 1 ? icmp : tcpudp;

    string line;
    while (getline(cin, line))
    {
        if (not (pat << line))
        {
            cout << "no match: " << line << '\n';
            continue;
        }

        cout << "#matches: " << pat.end() << '\n';

        for (size_t idx = 1; idx != pat.end(); ++idx)
        {
            cout << idx << ": " << 
                pat[idx] << '\n';
        }
        cout << '\n';
    }
}

