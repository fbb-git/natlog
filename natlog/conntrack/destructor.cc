#include "conntrack.ih"

Conntrack::~Conntrack()
{
    string endSeconds = to_string(time(0));     // pseudo end-seconds

    d_stdMsg << "monitoring conntrack ends" << endl;

    for (auto &rec: d_connections)
    {                                       // rec is a *, 0 for terminated
        if (rec)                            // connections
            (this->*
                (
                    rec->protocol == "icmp" ? 
                        &Conntrack::logIcmp
                    :
                        &Conntrack::logTcpudp
                )
            )(*rec, endSeconds, "0", "0", "0"); 
    }
}
