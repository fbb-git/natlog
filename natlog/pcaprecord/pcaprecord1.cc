#include "pcaprecord.ih"

PcapRecord::PcapRecord(std::ostream &out)
:
    d_out(out),
    d_options(Options::instance())
{}
