#include "conntrack.ih"

Conntrack::~Conntrack()
{
    string endSeconds = to_string(time(0));

    d_stdMsg << "terminating" << endl;

    for (auto &rec: d_connections)
    {
        if (rec)
            log(*rec, endSeconds, "0");
    }
}
