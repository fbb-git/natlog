#include "tcpdumpproducer.ih"

TcpdumpProducer::TcpdumpProducer(ostream &stdMsg, Storage &storage)
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_inName(d_options[0]),
    d_outName(d_options[3])
{
            //  device     address        mask
    g_nic.set(Record::IN,  d_options[1],  d_options[2]);
    g_nic.set(Record::OUT, d_options[4],  d_options[5]);
}
