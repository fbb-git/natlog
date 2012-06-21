#include "devices.ih"

Devices::Devices(ostream &stdMsg)
:
    d_record(stdMsg),
    d_options(Options::instance()),
    d_stdMsg(stdMsg)
{
}
