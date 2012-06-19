#include "natfork.ih"

NatFork::NatFork()
:
    d_options(Options::instance()),
    d_out(&d_msb)
{}
