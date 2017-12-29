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

    string line;
    while (getline(cin, line))
    {
        if (not (tcpudp << line))
        {
            cout << "no match: " << line << '\n';
            continue;
        }

        cout << "#matches: " << tcpudp.end() << '\n';

        for (size_t idx = 1; idx != tcpudp.end(); ++idx)
        {
            cout << idx << ": " << 
                tcpudp[idx] << '\n';
        }
        cout << '\n';
    }
}

