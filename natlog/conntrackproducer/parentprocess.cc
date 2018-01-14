#include "conntrackproducer.ih"

    // See also README.conntrack


void ConntrackProducer::parentProcess()
{
    string line;
    while (getline(cin, line))
        process(line);

    waitForChild();

    if (not d_stop)
    {
        cin.clear();
        throw Options::CONNTRACK_ENDED;
    }
}





