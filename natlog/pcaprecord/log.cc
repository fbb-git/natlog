#include "pcaprecord.ih"

void PcapRecord::log(Record const *record, time_t endSeconds, 
                                           suseconds_t endMicroSeconds) const
{
    ostringstream out1;

    out1 << "from " << 
                ShowSeconds(seconds(*record)) << ':' << 
                        setfill('0') << setw(6) << microSeconds(*record) << 
            " until " << 
                ShowSeconds(endSeconds) << ':' << 
                                        setw(6) << endMicroSeconds << 
                                        ShowSeconds::utcMarker() << ':';

    ostringstream out2;
    display(out2, record);

    if (d_options.stdout())
        cout << out1.str() << "\n"
                "   " << out2.str() << endl;

    d_syslog << out1.str() << out2.str() << endl;
}
