#include "conntrack.ih"

Conntrack::~Conntrack()
{
    string endSeconds = X2a(time(0));

    d_syslog << "terminating" << endl;

    for (auto rec: d_record)
        out(rec.second, endSeconds, "0000");
}
