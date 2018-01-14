#include "conntrackproducer.ih"

void ConntrackProducer::childRedirections()
{
    int fd[] = {STDOUT_FILENO, STDERR_FILENO};
    d_pipe.writtenBy(fd, 2);
}

