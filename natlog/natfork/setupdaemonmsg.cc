#include "natfork.ih"

void NatFork::setupDaemonMsg()
{
    if (not d_options.syslog())
    {
        imsg.off();
//        wmsg.off();

        return;
    }

                                // verbose msg via syslog, if syslog is active
    if (d_options.verbose())
        imsg.reset(*d_syslog);
    else
        imsg.off();

//                                // warning msg via syslog, if syslog is active
//    if (d_options.warnings())
//        wmsg.reset(*d_syslog);
//    else
//        wmsg.off();
}
