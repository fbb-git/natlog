#include "connectionsconsumer.ih"

unordered_map<Record::Protocol, void (ConnectionsConsumer::*)(Record *)> 
ConnectionsConsumer::s_handler = 
{
    { Record::ICMP,             &ConnectionsConsumer::icmp }, 
    { Record::TCP,              &ConnectionsConsumer::tcp }, 
    { Record::UDP,              &ConnectionsConsumer::udp }, 
};

pair<char const *, char const *> ConnectionsConsumer::s_logType[]
{
    { "",               "ok"         },
    { " (INCOMPLETE)",  "incomplete" },
    { " (EOP)",         "eop"        }
};

void (ConnectionsConsumer::*ConnectionsConsumer::s_tcpIn[]) (Record *) =
{
    &ConnectionsConsumer::tcpSyn,           // TCP_SYN
    &ConnectionsConsumer::tcpFin,           // TCP_FIN
    &ConnectionsConsumer::tcpSent,          // TCP_SENT
    &ConnectionsConsumer::tcpReceived,      // TCP_RECVD
    &ConnectionsConsumer::tcpIgnore         // TCP_IGNORE
};


