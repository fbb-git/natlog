#include "natfork.ih"

NatFork::~NatFork()
{
    cleanupPidFile();
}
