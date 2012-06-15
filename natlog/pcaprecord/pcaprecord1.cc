#include "pcaprecord.ih"

PcapRecord::PcapRecord(std::ostream &syslog)
:
    d_syslog(syslog),
    d_options(Options::instance())
{}
