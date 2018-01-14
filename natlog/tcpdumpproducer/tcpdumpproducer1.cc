#include "tcpdumpproducer.ih"

TcpdumpProducer::TcpdumpProducer(ostream &stdMsg, Storage &storage)
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_inName(d_options[1]),
    d_outName(d_options[2])
{}
