#include "devices.ih"

Devices::Devices(ostream &syslog)
:
    d_record(syslog),
    d_options(Options::instance())
{
}
