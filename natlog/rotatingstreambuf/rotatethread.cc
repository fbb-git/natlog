#include "rotatingstreambuf.ih"

void RotatingStreambuf::rotateThread()
{
    size_t nDays = Options::instance().logRotate();

    if (nDays == 0)
        return;

    while (true)
    {
        this_thread::sleep_for(chrono::hours(nDays));

        time_t now = time(0);
        ostringstream suffix;
        suffix << put_time(gmtime(&now), ".%F-%T");

        for (RotatingStreambuf *rs: s_rotate)
            rs->rotate(suffix.str());
    }
}
