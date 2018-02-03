#include "rotatingstreambuf.ih"

void RotatingStreambuf::rotate(std::string const &suffix)
{
    d_mutex.lock();

    d_out.close();
    rename(d_name.c_str(), (d_name + suffix).c_str());

    Exception::open(d_out, d_name);

    if (d_header)
        (*d_header)(d_out);

    d_mutex.unlock();
}
