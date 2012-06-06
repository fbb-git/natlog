#include "natfork.ih"

void NatFork::run()
{
    if (Options::instance().daemon())
        fork();
    else
        childProcess();
}
