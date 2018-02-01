#include "conntrackproducer.ih"

    // See also README.conntrack


void ConntrackProducer::parentProcess()
{
    string line;                // co-used for retrieving the IP Header size
    
    while (getline(cin, line))
        process(line);

    waitForChild();

    if (not d_signaled)
        d_stdMsg << "conntrack terminated" << endl;
}





