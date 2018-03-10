#include "record.ih"

void Record::setTime(size_t seconds, size_t microSeconds)
{
    d_inSeconds = seconds;
    d_inMicroSeconds = microSeconds;
}

