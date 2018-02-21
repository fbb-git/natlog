#include "tcp.ih"

void TCP::ignore(Record *next)
{
    delete next;
}
