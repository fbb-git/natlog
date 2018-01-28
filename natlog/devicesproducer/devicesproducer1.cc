#include "devicesproducer.ih"

DevicesProducer::DevicesProducer(ostream &stdMsg, Storage &storage)
:
    d_options(Options::instance()),
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_signaled(0)
{
    handleSignals();

    g_nic.set(Record::IN,  d_options[0]);
    g_nic.set(Record::OUT, d_options[1]);
}
