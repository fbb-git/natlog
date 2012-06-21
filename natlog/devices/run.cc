#include "devices.ih"

void Devices::run(ostream &parent)
{
    PcapFilter in(d_options[0], d_record, PcapRecord::IN);
    PcapFilter out(d_options[1], d_record, PcapRecord::OUT);

    parent << 0 << endl;                    // all OK

    Signal::instance().add(SIGTERM, in);
    Signal::instance().add(SIGTERM, out);

    d_stdMsg << "starting: capturing " << d_options[0] << 
                              " and " << d_options[1] << endl;

    thread inThread(in);
    thread outThread(out);

    inThread.join();
    outThread.join();
}





