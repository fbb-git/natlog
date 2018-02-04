#include "options.ih"

void Options::setTimeSpec()
{
    string value;
    if (not d_arg.option(&value, 't'))
        d_time = s_time.find("raw");
    else 
        setTimeType(value);

    if (d_mode == CONNTRACK)                // no TTL for conntrack
        d_ttl = ::time(0);

    else if (d_arg.option(&value, 'T'))
    {
        istringstream in{ value };
        for (size_t count = 0; count != 2; ++count)
        {
            size_t seconds;
            in >> seconds;

            switch (in.get())
            {
                case 'u':
                    d_ttl = seconds;
                break;

                case 't':
                    d_ttlTCP = seconds;
                break;

                case EOF:
                return;

                default:
                throw Exception{} << "`--ttl " << value << "' not supported";
            }
        }
    }
}

