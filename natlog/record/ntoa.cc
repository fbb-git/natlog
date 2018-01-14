#include "record.ih"

// typedef uint32_t in_addr_t;
// struct in_addr {
//     uint32_t s_addr;  // load with inet_aton()
// };

// static
char *Record::ntoa(uint32_t ipAddr)
{
    return inet_ntoa( { ipAddr } );
}
