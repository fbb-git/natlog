#include "rotatingstreambuf.ih"

// assume nRotations == 3
// x.2 -> x.3   if x.2 exists, rotate
// x.1 -> x.2   if x.1 exists, rotate.
// x   -> x.1

void RotatingStreambuf::rotate(size_t nRotations)
{
    {
        lock_guard<mutex> lg{ d_mutex };
        if (not d_contents)                     // no contents, nothing to
            return;                             // rotate
    }

    string name = d_name + '.';
    string newName = name + to_string(nRotations);

    for (; --nRotations; )      
    {
        string oldName = name + to_string(nRotations);
        char const *old = oldName.c_str();

        if (access(old, F_OK) == 0)             // file exists
            rename(old, newName.c_str());       // rename it.

        newName = move(oldName);
    }
            
    lock_guard<mutex> lg{d_mutex};

    d_out.close();

    rename(d_name.c_str(), newName.c_str());

    Exception::open(d_out, d_name);

    if (d_header)
        (*d_header)(d_out);

    d_contents = false;
}
