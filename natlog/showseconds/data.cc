#include "showseconds.ih"

void (*ShowSeconds::s_show)(std::ostream &out, std::string const &time) =
        ShowSeconds::rawTime;

string ShowSeconds::s_utcMarker;
