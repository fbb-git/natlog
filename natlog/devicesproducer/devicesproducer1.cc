#include "devicesproducer.ih"

DevicesProducer::DevicesProducer(ostream &stdMsg, Storage &storage)
:
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_signaled(0)
{
    Options const &options = Options::instance();
    d_inName = options[0];
    d_outName = options[1];

    handleSignals();

    g_nic.set(Record::IN,  d_inName);
    g_nic.set(Record::OUT, d_outName);
}
