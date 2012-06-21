#include "pcaprecord.ih"

PcapRecord::PcapRecord(std::ostream &stdMsg)
:
    d_stdMsg(stdMsg),
    d_options(Options::instance())
{}
