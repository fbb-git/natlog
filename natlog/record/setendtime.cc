#include "record.ih"

void Record::setEndTime(Record const *other)
{
    d_seconds = other->d_inSeconds;
    d_microSeconds = other->d_inMicroSeconds;

    d_lastUsed = ::time(0);
}
