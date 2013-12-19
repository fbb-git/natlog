#include "devices.ih"

Devices::Devices(ostream &stdMsg, ostream &parent)
:
    d_record(stdMsg),
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_parent(parent)
{
}
