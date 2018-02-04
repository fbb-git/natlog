#include "options.ih"

void Options::setTimeType(string const &spec)
{
    d_time = s_time.find(spec);
    if (d_time == s_time.end())
    {
        d_time = s_time.find("raw");
        d_timeSpecError = spec;
    }
}
