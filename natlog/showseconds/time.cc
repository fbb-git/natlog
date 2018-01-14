#include "showseconds.ih"

namespace
{
    void insertTime(DateTime::TimeType type, 
                    std::ostream &out, size_t seconds)
    {
        
        DateTime dt(static_cast<time_t>(seconds), type);
        ostringstream os;
        os << dt;
            // E.g., 'Sun Nov 2 13:29:11 2008'
            //        01234             56789
        out << os.str().substr(4, os.str().length() - 9);
    }
}

void ShowSeconds::rawTime(ostream &out, size_t seconds)
{
    out << seconds;
}

void ShowSeconds::utcTime(ostream &out, size_t seconds)
{
    insertTime(DateTime::UTC, out, seconds);
}

void ShowSeconds::localTime(ostream &out, size_t seconds)
{
    insertTime(DateTime::LOCALTIME, out, seconds);
}

string ShowSeconds::now()
{
    ostringstream out;

    out << ShowSeconds{ static_cast<size_t>(time(0)) } << ":000000";

    return out.str();
}

