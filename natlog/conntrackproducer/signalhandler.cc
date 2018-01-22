#include "conntrackproducer.ih"

void ConntrackProducer::signalHandler(size_t signum)
{
    if (signum == SIGHUP)
    {
        d_stdMsg << "ignoring signal SIGHUP" << endl;
        return;
    }

    d_stdMsg << "received signal " << signum << " (" << 
        (signum == SIGINT ? "SIGINT" : "SIGTERM") << ')' << endl;

    d_stop = true;

    kill(pid(), SIGTERM);
    kill(pid(), SIGTERM);
    kill(pid(), SIGKILL);
}
