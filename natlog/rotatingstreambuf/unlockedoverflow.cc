#include "rotatingstreambuf.ih"

int RotatingStreambuf::unlockedOverflow(int ch)
{
    d_mutex.lock();
    d_locked = true;
    d_overflow = &RotatingStreambuf::lockedOverflow;

    return d_out.rdbuf()->sputc(ch);
}
