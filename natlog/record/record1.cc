#include "record.ih"

Record::Record(Type type, size_t seconds, size_t muSeconds,  
               u_char const *packet)
:
    d_protocol(static_cast<Protocol>(get<IP_Header>(packet).protocol)),
    d_type(type),

    d_seconds(seconds),
    d_microSeconds(muSeconds),
    d_inSeconds(seconds),
    d_inMicroSeconds(muSeconds),

    d_sourceIP(get<IP_Header>(packet).sourceAddr.s_addr),
    d_destIP(get<IP_Header>(packet).destAddr.s_addr),

    d_lastUsed(::time(0))
{}    

