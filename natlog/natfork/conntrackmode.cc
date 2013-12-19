#include "natfork.ih"

void NatFork::conntrackMode()
{
    string conntrack = d_options.conntrackCommand();

    d_stdMsg << "CONNTR: " << conntrack << endl;

    size_t pos = conntrack.find_first_of(" \t");
    if (pos != string::npos)
        conntrack.resize(pos);

    if (access(conntrack.c_str(), R_OK | X_OK) != 0)
    {
        d_stdMsg << "[Fatal] Can't execute " << conntrack << endl;
        throw Options::FAILED;
    }
    d_mode = CONNTRACK;
}
