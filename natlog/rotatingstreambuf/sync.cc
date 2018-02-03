#include "rotatingstreambuf.ih"

int RotatingStreambuf::sync()
{
    if (not d_locked)
        d_mutex.lock();

    int ret = d_out.rdbuf()->pubsync();
    d_overflow = &RotatingStreambuf::unlockedOverflow;
    d_mutex.unlock();
    
    return ret;
}
