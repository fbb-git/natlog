#include "conntrack.ih"

void Conntrack::signalHandler(size_t signum)
{
    d_conntrack.stop();
}
