#include "nic.ih"

void NIC::set(Record::Type type, string const &name)
try
{
    ifaddrs *ifaddr;

    if (getifaddrs(&ifaddr) == -1) 
        throw 1;

    for (ifaddrs const *ifa = ifaddr; ifa != 0; ifa = ifa->ifa_next) 
    {
                                                // find the requested name
        if (                                    // and family
            ifa->ifa_addr == 0 || name != ifa->ifa_name ||
            ifa->ifa_addr->sa_family != AF_INET
        )
            continue;

        d_nic[type] =                           // found it.
            {
                ntohl(
                    reinterpret_cast<sockaddr_in *>(
                                        ifa->ifa_addr)->sin_addr.s_addr
                ),
                ntohl(
                    reinterpret_cast<sockaddr_in *>(
                                        ifa->ifa_netmask)->sin_addr.s_addr
                )
            };

        freeifaddrs(ifaddr);
        return;
    }

    throw 1;
}
catch (int)
{
    throw Exception() << "cannot retrieve NIC info for `" << name << '\'';
}
