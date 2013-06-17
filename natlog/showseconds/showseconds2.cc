#include "showseconds.ih"

ShowSeconds::ShowSeconds(time_t seconds)
:
    d_seconds(to_string(seconds))
{}
