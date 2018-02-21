#include "connectionsconsumer.ih"

ConnectionsConsumer::ConnectionsConsumer(ostream &stdMsg, Storage &storage)
:
    d_options(Options::instance()),
    d_logDataStream(header),
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_icmp(stdMsg, d_logDataStream),
    d_udp(stdMsg, d_logDataStream),
    d_tcp(stdMsg, d_logDataStream),
    d_handler
    {
        { Record::ICMP,     &d_icmp }, 
        { Record::TCP,      &d_tcp  }, 
        { Record::UDP,      &d_udp  }, 
    },
    d_ttl(d_options.ttl())
{
    string path;
    if (ArgConfig::instance().option(&path, "log-data") != 0)
        d_logDataStream.open(path);                 // prepare for data log

    Signal::instance().add(SIGINT, *this);
    Signal::instance().add(SIGTERM, *this);
}

