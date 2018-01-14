#include "showseconds.ih"

void (*ShowSeconds::s_show)(std::ostream &out, size_t time) =
        ShowSeconds::rawTime;

string ShowSeconds::s_utcMarker;
