#include "rotatingstreambuf.ih"

void RotatingStreambuf::notify()
{
    if (not s_rotate.empty())
    {
        s_semaphore.notify();
        s_rotateThread.join();
    }
}
       
