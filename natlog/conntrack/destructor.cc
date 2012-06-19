#include "conntrack.ih"

Conntrack::~Conntrack()
{
    string endSeconds = X2a(time(0));

    d_out << "terminating" << endl;

    for (auto &rec: d_connections)
    {
        if (rec)
            log(*rec, endSeconds, "0");
    }
}
