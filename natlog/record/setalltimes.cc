#include "record.ih"

void Record::setAllTimes(size_t seconds, size_t microSeconds)
{
    d_seconds = d_inSeconds = seconds;
    d_microSeconds = d_inMicroSeconds = microSeconds;
    d_lastUsed = ::time(0);
}

