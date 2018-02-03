#include "rotatingstreambuf.ih"

void RotatingStreambuf::rotate(RotatingStreambuf *rs)
{
    while (true)
    {
        this_thread::sleep_for(chrono::hours(rs->d_nDays));

        time_t now = time(0);
        ostringstream suffix;
        suffix << put_time(gmtime(&now), ".%F-%T");

        rs->d_mutex.lock();

        rs->d_out.close();
        rename(rs->d_name.c_str(), (rs->d_name + suffix.str()).c_str());

        Exception::open(rs->d_out, rs->d_name);

        if (rs->d_header)
            (*rs->d_header)(rs->d_out);

        rs->d_mutex.unlock();
    }
}
