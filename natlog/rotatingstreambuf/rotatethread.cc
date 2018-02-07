#include "rotatingstreambuf.ih"

void RotatingStreambuf::rotateThread()
{
    Options const &options = Options::instance();

    size_t freq = options.rotateFreq();
    size_t nRotations = options.nRotations();

    if (freq == 0 || nRotations == 0)
        return;

    freq *= options.rotateFactor();

    while (s_semaphore.wait_for(chrono::minutes(freq)) == cv_status::timeout)
    {
        for (RotatingStreambuf *rs: s_rotate)
            rs->rotate(nRotations);
    }
}
