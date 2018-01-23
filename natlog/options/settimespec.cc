#include "options.ih"

void Options::setTimeSpec()
{
    string value;
    if (not d_arg.option(&value, 't'))
        d_time = s_time.find("raw");
    else 
        setTime(value);

    if (d_mode == CONNTRACK)                // no TTL for conntrack
        d_ttlTCP = d_ttl = ::time(0);
    else
    {                                       // process 1st 2 -T options
        for (
            size_t count = min(size_t(2), d_arg.option(&value, 'T')); 
                count--; 
                    // no increment
        )
        {
            size_t seconds = stoul(value);
            if (value.back() == 's')
                d_ttlTCP = seconds;
            else
                d_ttl = seconds;
        }
    }
}
