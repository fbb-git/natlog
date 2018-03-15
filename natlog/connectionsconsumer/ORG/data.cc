#include "connectionsconsumer.ih"

//unordered_map<Record::Protocol, IPbase*> 
//ConnectionsConsumer::s_handler = 
//{
//    { Record::ICMP,     &d_icmp }, 
//    { Record::TCP,      &d_tcp  }, 
//    { Record::UDP,      &d_udp  }, 
//};

//pair<char const *, char const *> ConnectionsConsumer::s_logType[]
//{
//    { "",               "ok"         },
//    { " (EXPIRED)",  "expired" },
//    { " (EOP)",         "eop"        }
//};

//void (ConnectionsConsumer::*ConnectionsConsumer::s_tcpIn[]) (Record *) =
//{
//    &ConnectionsConsumer::tcpSyn,           // TCP_SYN
//    &ConnectionsConsumer::tcpFin,           // TCP_FIN
//    &ConnectionsConsumer::tcpSent,          // TCP_SENT
//    &ConnectionsConsumer::tcpReceived,      // TCP_RECVD
//    &ConnectionsConsumer::tcpIgnore         // TCP_IGNORE
//};
//

