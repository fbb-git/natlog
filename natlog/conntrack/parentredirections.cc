#include "conntrack.ih"

void Conntrack::parentRedirections()
{
    d_pipe.readFrom(STDIN_FILENO);
}
