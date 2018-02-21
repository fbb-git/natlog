#include "tcp.ih"

void (TCP::*TCP::s_tcpIn[]) (Record *) =
{
    &TCP::syn,           // TCP_SYN
    &TCP::fin,           // TCP_FIN
    &TCP::sent,          // TCP_SENT
    &TCP::received,      // TCP_RECVD
    &TCP::ignore         // TCP_IGNORE
};
