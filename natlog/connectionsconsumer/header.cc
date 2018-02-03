#include "connectionsconsumer.ih"

void ConnectionsConsumer::header(ostream &log)
{
    log <<
                    "type," <<

        setw(11) << "srcNr"     << ',' <<
        setw(16) << "srcIP"     << ',' <<
        setw(8)  << "srcPort"   << ',' <<

        setw(11) << "dstNr"     << ',' <<
        setw(16) << "dstIP"     << ',' <<
        setw(8)  << "dstPort"   << ',' <<

        setw(11) << "sent"      << ',' <<
        setw(11) << "recvd"     << ',' <<

        setw(11) << "begin"     << ',' <<
        setw(11) << "end"       << ", " <<

        setw(22) << "beginTime" << ", " <<
        setw(23) << "endTime"   << ", complete" << endl;
                                 // 1234567
}
