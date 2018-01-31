#include "connectionsconsumer.ih"

ConnectionsConsumer::ConnectionsConsumer(ostream &stdMsg, Storage &storage)
:
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_ttl(Options::instance().ttl())
{
    string path;
    if (ArgConfig::instance().option(&path, "log-data") == 0)
        d_logData = &ConnectionsConsumer::noDataLog;
    else
    {
        bool existing = access(path.c_str(), F_OK) == 0;

        d_logData = &ConnectionsConsumer::logData;
        Exception::open(d_logDataStream, path, 
                                    existing ?
                                        ios::in | ios::ate : ios::out);
        if (not existing)
            d_logDataStream <<
                        "type," <<

            setw(11) << "srcNr"     << ',' <<
            setw(16) << "srcIP"     << ',' <<
            setw(8)  << "srcPort"   << ',' <<

            setw(11) << "dstNr"     << ',' <<
            setw(16) << "dstIP"     << ',' <<
            setw(8)  << "dstPort"   << ',' <<

            setw(10) << "sent"      << ',' <<
            setw(10) << "recvd"     << ',' <<

            setw(11) << "begin"     << ',' <<
            setw(11) << "end"       << ", " <<

            setw(22) << "beginTime" << ", " <<
            setw(23) << "endTime\n";
    }
}
