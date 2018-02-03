#include "record.ih"

// static
string Record::time(size_t seconds, size_t microSeconds)
{
    ostringstream out;
    
    out << ShowSeconds{ seconds } << ':' << setfill('0') << setw(6) <<
                microSeconds;

    return out.str();
}
