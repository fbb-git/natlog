#include "showseconds.ih"

ostream &operator<<(ostream &out, ShowSeconds const &showSeconds)
{
    (*ShowSeconds::s_show)(out, showSeconds.d_seconds);
    return out;
}
