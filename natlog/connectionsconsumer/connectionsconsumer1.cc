#include "connectionsconsumer.ih"

ConnectionsConsumer::ConnectionsConsumer(ostream &stdMsg, Storage &storage)
:
    d_options(Options::instance()),
    d_logDataStream(header),
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_ttl(d_options.ttl())
{
    string path;
    if (ArgConfig::instance().option(&path, "log-data") == 0)
        d_logData =  &ConnectionsConsumer::noDataLog;
    else
    {
        d_logData = &ConnectionsConsumer::logData;  // member logging data
        d_logDataStream.open(path);                 // prepare for data log
    }

    Signal::instance().add(SIGINT, *this);
    Signal::instance().add(SIGTERM, *this);
}

