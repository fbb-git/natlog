#include "devicesproducer.ih"

void DevicesProducer::run()
{
                                        // see pcapfilter/callback for
                                        // handling incoming packets
    thread{                          
        PcapFilter {d_options[0], Record::IN, d_stdMsg, d_storage }
    }.detach();

                                        // the out object handles signals
    PcapFilter out{ d_options[1], Record::OUT, d_stdMsg, d_storage };

    d_stdMsg << "starting capturing " << d_options[0] << 
                              " and " << d_options[1] << endl;

    out();    

    if (not out.signaled())
        d_stdMsg << "capturing network devices terminated" << endl;
}





