#include "rotatingstreambuf.ih"

void RotatingStreambuf::rotateThread()
{
    Options const &options = Options::instance();

    size_t freq = options.rotateFreq();
    size_t nRotations = options.nRotations();

    if (freq == 0 || nRotations == 0)
        return;

    freq *= options.rotateFactor();

    while (true)
    {
        this_thread::sleep_for(chrono::minutes(freq));

        for (RotatingStreambuf *rs: s_rotate)
            rs->rotate(nRotations);
    }
}
