#include "showtime.ih"

namespace
{
    void insertTime(DateTime::TimeType type, 
                    std::ostream &out, std::string const &seconds)
    {
        
        DateTime dt(static_cast<time_t>(A2x(seconds)), type);
        ostringstream os;
        os << dt;
            // E.g., 'Sun Nov 2 13:29:11 2008'
            //        01234             56789
        out << os.str().substr(4, os.str().length() - 9);
    }
}

void ShowTime::rawTime(ostream &out, string const &seconds)
{
    out << seconds;
}

void ShowTime::utcTime(ostream &out, string const &seconds)
{
    insertTime(DateTime::UTC, out, seconds);
}

void ShowTime::localTime(ostream &out, string const &seconds)
{
    insertTime(DateTime::LOCALTIME, out, seconds);
}
