#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#include <iostream>
#include <string>

using namespace std;


int main(int argc, char **argv)
{

    if (argc == 1)
    {
        cout << "provide name(s) of interface(s) to inspect\n";
        return 0;
    }

    ifaddrs *ifaddr;

    if (getifaddrs(&ifaddr) == -1) 
    {
        cout << "getifaddrs failed\n";
        return 1;
    }

    cout << hex;

    size_t n = 0;
    for (ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next, ++n) 
    {
        if (ifa->ifa_addr == 0)
            continue;

        string name = ifa->ifa_name;
        bool requested = false;
        for (size_t idx = 1, end = argc; idx != end; ++idx)
        {
            if (name == argv[idx])
            {
                requested = true;
                break;
            }
        }
        if (not requested)
            continue;
        
        size_t family = ifa->ifa_addr->sa_family;

        if (family != AF_INET)
            continue;

        auto ptr = reinterpret_cast<sockaddr_in *>(ifa->ifa_addr);

        cout << name << "\n"
            "   address = " << 
            ntohl(ptr->sin_addr.s_addr) <<
            ' ' << inet_ntoa(ptr->sin_addr) << '\n';

        ptr = reinterpret_cast<sockaddr_in *>(ifa->ifa_netmask);
        cout <<"      mask = " << 
            ntohl(ptr->sin_addr.s_addr) <<
            ' ' << inet_ntoa(ptr->sin_addr) << 
            '\n';
    }
    
    freeifaddrs(ifaddr);
}
