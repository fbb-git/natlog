#include "rotatingstreambuf.ih"

void RotatingStreambuf::notify()
{
    s_semaphore.notify();
    s_rotateThread.join();
}
       
