#include "options.ih"

void Options::setTime(string const &spec)
{
    auto iter = s_time.find(spec);
    if (iter != s_time.end())
    {
        if (d_verbose)
            cout << "Time specification: " << spec << endl;
        d_time = iter->second;
    }
    else
        emsg << "Time specification `" << spec << "' not supported. "
                "(see the man-page)" << endl;
}
