#include "conntrackproducer.ih"

    // See also README.conntrack


void ConntrackProducer::parentProcess()
{
    string line;
    while (getline(cin, line))
        process(line);

    waitForChild();

    d_storage.setEmpty();       // to end the consumer

    if (not d_stop)
    {
        d_stdMsg << "conntrack terminated" << endl;
        d_stop = true;
    }
}





