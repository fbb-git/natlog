#include "natfork.ih"

void NatFork::conntrackMode()           // check the availability of the 
{                                       // conntrack device
    string conntrack = d_options.conntrackCommand();

    size_t pos = conntrack.find_first_of(" \t");
    if (pos != string::npos)
        conntrack.resize(pos);

    if (access(conntrack.c_str(), R_OK | X_OK) != 0)
    {
        d_stdMsg << "[Fatal] can't execute " << conntrack << endl;
        throw 1; 
    }
}
