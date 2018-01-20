#include "conntrackproducer.ih"

    // See also README.conntrack


void ConntrackProducer::parentProcess()
{
    string line;
    while (getline(cin, line))
        process(line);

    waitForChild();

    if (d_stop)
        d_storage.setEmpty();
    else
    {
        cin.clear();
        throw Options::TERM_SIGNAL;
    }
}





