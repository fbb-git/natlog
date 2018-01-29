#include "devicesproducer.ih"

void DevicesProducer::run()
{
    PcapFilter in{ d_inName, Record::IN, d_stdMsg, d_storage };
    PcapFilter out{ d_outName, Record::OUT, d_stdMsg, d_storage };

    thread{ in }.detach();
    thread{ out }.detach();

    d_stdMsg << "starting capturing " << d_inName << " and " << d_outName << endl;

    d_signaled.wait();
    d_endSignal = true;

    in.stop();
    out.stop();

    d_stdMsg << "monitoring " << d_inName << " and " << d_outName << " ends" << endl;
}





