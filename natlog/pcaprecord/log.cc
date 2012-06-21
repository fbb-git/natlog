#include "pcaprecord.ih"

void PcapRecord::log(Record const *record, time_t endSeconds, 
                                           suseconds_t endMicroSeconds) const
{
    d_stdMsg << "from " << 
                ShowSeconds(seconds(*record)) << ':' << 
                        setfill('0') << setw(6) << microSeconds(*record) << 
            " until " << 
                ShowSeconds(endSeconds) << ':' << 
                                        setw(6) << endMicroSeconds << 
                                        ShowSeconds::utcMarker() << ": ";

    display(d_stdMsg, record) << endl;
}
