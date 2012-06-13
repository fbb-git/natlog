#include "pcapfilter.ih"

char PcapFilter::s_filterExpr[] =
    "host 129.125.3.162 and ( tcp[13] == 0x12"           // SYN,ACK
    " or "
    "tcp[13] == 0x11 )";          // FIN,ACK

mutex PcapFilter::s_recordMutex;
