#include "pcaprecord.ih"

ostream &PcapRecord::display(ostream &out, Record const *record) const
{
    Address &&src = sourceIP(*record);
    Address &&via = viaIP(*record);
    Address &&dst = destIP(*record);

    return out << ' ' << 
                src.dottedDecimalAddress() << ':' << src.port() << 
           " (via: " << 
                via.dottedDecimalAddress() << ':' << via.port() << ") "
            "to " << 
                dst.dottedDecimalAddress() << ':' << dst.port();
}
