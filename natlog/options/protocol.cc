#include "options.ih"

string Options::protocol(string const &available, string &spec)
{
    string ret;

    size_t pos = spec.find(available);
    if (pos != string::npos)
    {
        spec.erase(pos, available.length() + 1);    // + 1 to remove the :
        ret = " -p " + available;
    }
    return ret;
}
