#include "conntrackrecord.ih"

void ConntrackRecord::erase(size_t idx)
{
    delete d_connections[idx];
    imsg << "Erased #" << idx << endl;
    d_connections[idx] = 0;
}
