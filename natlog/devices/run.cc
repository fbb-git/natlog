#include "devices.ih"

void Devices::run()
{
    PcapFilter in(d_options[0], d_record, PcapFilter::IN);
    PcapFilter out(d_options[1], d_record, PcapFilter::OUT);

    Signal::instance().add(SIGTERM, in);
    Signal::instance().add(SIGTERM, out);

    thread inThread(in);
    thread outThread(out);

    inThread.join();
    outThread.join();
}





