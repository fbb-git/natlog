#include "rotatingstreambuf.ih"

void RotatingStreambuf::open(string const &name)
{
    d_name = name;
    d_overflow = &RotatingStreambuf::unlockedOverflow;

    bool existing = access(name.c_str(), F_OK) == 0;

    Exception::open(d_out, name, existing ? ios::in | ios::ate : ios::out);
    if (not existing and d_header)
        (*d_header)(d_out);

    s_rotate.push_back(this);
}
