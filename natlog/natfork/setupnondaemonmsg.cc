#include "natfork.ih"

void NatFork::setupNonDaemonMsg()
{
    if (not d_options.verbose())
        imsg.off();

    if (not d_options.warnings())
        wmsg.off();
}
