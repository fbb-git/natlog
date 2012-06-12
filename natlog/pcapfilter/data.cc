#include "pcapfilter.ih"

char PcapFilter::s_filterExpr[] =
    "tcp[13] == 0x12"           // SYN,ACK
    " or "
    "tcp[13] == 0x11";          // FIN,ACK

mutex PcapFilter::s_recordMutex;
