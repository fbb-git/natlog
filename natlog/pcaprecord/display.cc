#include "pcaprecord.ih"

void PcapRecord::display(Record const *record) const
{
    Address &&src = sourceIP(*record);
    Address &&via = viaIP(*record);
    Address &&dst = destIP(*record);

    cout << seconds(*record) << ':' << microSeconds(*record) << 
            " from " <<
                src.dottedDecimalAddress() << " (" << src.port() << "), " 
            "via " <<
                via.dottedDecimalAddress() << " (" << via.port() << "), "
            "to " <<
                dst.dottedDecimalAddress() << " (" << dst.port() << 
            ")\n";
}
