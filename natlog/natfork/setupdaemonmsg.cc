#include "natfork.ih"

void NatFork::setupDaemonMsg()
{
    if (d_options.log().empty())
    {
        imsg.off();
        return;
    }
                                // verbose msg via syslog, if syslog is active
    if (d_options.verbose())
        imsg.reset(*d_syslog);
    else
        imsg.off();
}
