#include "showseconds.ih"

void (*ShowSeconds::utcFormat())(std::ostream &, size_t)
{
    auto ret = s_show;
    s_show = utcTime;
    return ret;
}
