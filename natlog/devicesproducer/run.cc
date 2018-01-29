#include "devicesproducer.ih"

void DevicesProducer::run()
{
    PcapFilter in{ d_in, Record::IN, d_stdMsg, d_storage };
    PcapFilter out{ d_out, Record::OUT, d_stdMsg, d_storage };

    thread{ in }.detach();
    thread{ out }.detach();

    d_stdMsg << "starting capturing " << d_in << " and " << d_out << endl;

    d_signaled.wait();
    d_endSignal = true;

    in.stop();
    out.stop();

    d_stdMsg << "monitoring " << d_in << " and " << d_out << " ends" << endl;
}





