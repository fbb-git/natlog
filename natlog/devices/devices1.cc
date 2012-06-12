#include "devices.ih"

Devices::Devices(SyslogStream &syslog)
:
    d_options(Options::instance()),
    d_syslog(syslog)
{
}
