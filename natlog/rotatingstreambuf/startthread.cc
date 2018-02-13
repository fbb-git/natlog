#include "rotatingstreambuf.ih"

// static
void RotatingStreambuf::startThread()
{
    if (not s_rotate.empty())
        s_rotateThread = thread{ rotateThread };
}
