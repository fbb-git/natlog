#include "devices.ih"

Devices::Devices(ostream &out)
:
    d_record(out),
    d_options(Options::instance()),
    d_out(out)
{
}
