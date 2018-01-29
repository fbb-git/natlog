#include "devicesproducer.ih"

DevicesProducer::DevicesProducer(ostream &stdMsg, Storage &storage)
:
    d_stdMsg(stdMsg),
    d_storage(storage),
    d_signaled(0)
{
    Options const &options = Options::instance();
    d_in = options[0];
    d_out = options[3];

    handleSignals();

            //  device:    address      mask
    g_nic.set(Record::IN,  options[1],  options[2]);
    g_nic.set(Record::OUT, options[4],  options[5]);
}
