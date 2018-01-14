#include "conntrackproducer.ih"

void ConntrackProducer::signalHandler(size_t signum)
{
    if (signum == SIGHUP)
    {
        d_stdMsg << "ignoring signal SIGHUP for pid " << pid() << endl;
        return;
    }

    d_stdMsg << "stopping pid " << pid() << " on signal " << signum << endl;

    d_stop = true;

    kill(pid(), SIGTERM);
    kill(pid(), SIGTERM);
    kill(pid(), SIGKILL);
}
