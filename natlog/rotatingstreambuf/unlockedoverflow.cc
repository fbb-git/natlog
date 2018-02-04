#include "rotatingstreambuf.ih"

int RotatingStreambuf::unlockedOverflow(int ch)
{
    d_mutex.lock();
    d_locked = true;
    d_overflow = &RotatingStreambuf::lockedOverflow;
    d_contents = true;
    return d_out.rdbuf()->sputc(ch);
}
