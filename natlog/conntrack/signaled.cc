#include "conntrack.ih"

void Conntrack::signaled(size_t signum)
{
    d_conntrack.stop();
}
