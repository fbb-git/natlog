#include "record.ih"

Record::Record(Type type, size_t seconds, size_t muSeconds)
:
    d_type(type),
    d_seconds(seconds),
    d_microSeconds(muSeconds),
    d_inSeconds(seconds),
    d_inMicroSeconds(muSeconds),
    d_lastUsed(::time(0))
{}    

