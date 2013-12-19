#include "conntrack.ih"

void Conntrack::signalHandler(size_t signum)
{
    if (signum != SIGTERM && signum != SIGKILL)
        return;

    d_stdMsg << "Stopping natlog on receiving signal " << signum << "\n"
                "Ending conntrack having pid " << pid() << endl;

    d_stop = true;

    kill(pid(), SIGTERM);
    kill(pid(), SIGTERM);
    kill(pid(), SIGKILL);
}
