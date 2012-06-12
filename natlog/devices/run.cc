#include "devices.ih"

#include <signal.h>

namespace
{
    PcapFilter *pin;
    PcapFilter *pout;

    void signore(int)
    {
        pin->stop();
        pout->stop();

        cout << "Got sighup\n";
    }
}

void Devices::run()
{
    signal(SIGHUP, signore);

    PcapFilter in(d_options[0], d_record, PcapFilter::IN);
    PcapFilter out(d_options[1], d_record, PcapFilter::OUT);

    pin = &in;
    pout = &out;

    thread inThread(in);
    thread outThread(out);

    inThread.join();
    outThread.join();

    cout << "Leaving Devices::run()\n";
}





