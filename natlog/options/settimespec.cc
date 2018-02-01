#include "options.ih"

void Options::setTimeSpec()
{
    string value;
    if (not d_arg.option(&value, 't'))
        d_time = s_time.find("raw");
    else 
        setTime(value);

    if (d_mode == CONNTRACK)                // no TTL for conntrack
        d_ttl = ::time(0);
    else if (d_arg.option(&value, 'T'))
        d_ttl = stoul(value);
}

