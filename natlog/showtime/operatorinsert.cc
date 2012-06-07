#include "showtime.ih"

ostream &operator<<(ostream &out, ShowTime const &showTime)
{
    (*ShowTime::s_show)(out, showTime.d_seconds);
    return out;
}
