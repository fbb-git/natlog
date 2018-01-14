#include "conntrackproducer.ih"

void ConntrackProducer::parentRedirections()
{
    d_pipe.readFrom(STDIN_FILENO);
}
