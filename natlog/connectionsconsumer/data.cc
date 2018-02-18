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
    &ConnectionsConsumer::synRecord,        // TCP_SYN
    &ConnectionsConsumer::finRecord,        // TCP_FIN
    &ConnectionsConsumer::sentRecord,       // TCP_SENT
    &ConnectionsConsumer::receivedRecord,   // TCP_RECVD
    &ConnectionsConsumer::ignoreRecord      // TCP_IGNORE
};


