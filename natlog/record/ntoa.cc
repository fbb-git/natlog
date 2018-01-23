#include "record.ih"

// static
char *Record::ntoa(uint32_t ipAddr)
{
    return inet_ntoa( { ipAddr } );
}
