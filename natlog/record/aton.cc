#include "record.ih"

// static
size_t Record::aton(string const &addr)
{
    return inet_addr(addr.c_str());
}
