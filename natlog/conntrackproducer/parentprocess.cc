#include "conntrackproducer.ih"

    // See also README.conntrack


void ConntrackProducer::parentProcess()
{
    string line;                // co-used for retrieving the IP Header size
    
    size_t ipHeaderSize = 
            ArgConfig::instance().option(&line, "conntrack-ip-header-size") ?
                stoul(line)
            :
                0;

    while (getline(cin, line))
        process(line, ipHeaderSize);

    waitForChild();

    d_storage.setEmpty();       // ends the consumer

    if (not d_signaled)
        d_stdMsg << "conntrack terminated" << endl;
}





