#include "natfork.ih"

void NatFork::conntrackMode()
{
    Options &options = Options::instance();

    char const *conntrack = options.conntrackPath().c_str();

    if (access(conntrack, R_OK | X_OK) != 0)
    {
        d_stdMsg << "[Fatal] Can't execute " << conntrack << endl;
        throw Options::FAILED;
    }
    d_mode = CONNTRACK;
}
