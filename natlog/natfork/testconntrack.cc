#include "natfork.ih"

void NatFork::conntrackMode()
{
    char const *conntrack = d_options.conntrackPath().c_str();

    if (access(conntrack, R_OK | X_OK) != 0)
    {
        d_stdMsg << "[Fatal] Can't execute " << conntrack << endl;
        throw 1;
    }
    d_mode = CONNTRACK;
}
