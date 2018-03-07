#include "tcp.ih"

void TCP::inDev(RecordPtr &record)
{
    (this->*s_tcpIn[inType(*record)])(record);

        // syn;        // TCP_SYN
        // fin;        // TCP_FIN
        // sent;       // TCP_SENT
        // received;   // TCP_RECVD
        // ignore;     // TCP_IGNORE
}


