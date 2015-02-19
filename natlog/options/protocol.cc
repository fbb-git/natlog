#include "options.ih"

string Options::protocol(string const &available, string &spec)
{
    string ret;
    bool specified = false;

    while (true)
    {
        size_t pos = spec.find(available);
        if (pos == string::npos)
            break;

        spec.erase(pos, available.length() + 1);    // + 1 to remove the :
        specified = true;
    }

    if (specified)
    {
        d_conntrackProtocol += available;
        ret = " -p " + available;
    }

    return ret;
}
