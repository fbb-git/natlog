#include "devicesproducer.ih"

void DevicesProducer::run()
{
    PcapFilter in{ d_inName, Record::IN, d_stdMsg, d_storage
,true };
    PcapFilter out{ d_outName, Record::OUT, d_stdMsg, d_storage };

    thread { in }.detach();
    thread { out }.detach();

    d_stdMsg << "starting capturing " << d_inName << " and " << d_outName <<
                                                                        endl; 

    d_signaled.wait();

    d_stdMsg << "DevicesProducer signaled" << endl;

    d_endSignal = true;

    in.stop();
    out.stop();

//    inThread.join();
//    outThread.join();

    d_stdMsg << "monitoring " << d_inName << " and " << d_outName << 
                                                            " ends" << endl;
}





