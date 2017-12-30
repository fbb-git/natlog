#include "pcaprecord.ih"

ostream &PcapRecord::display(ostream &stdMsg, Record const *record) const
{
    Address &&src = sourceIP(*record);
    Address &&via = viaIP(*record);
    Address &&dst = destIP(*record);

    return stdMsg << ' ' << 
                src.dottedDecimalAddress() << ':' << src.port() << 
           " (via: " << 
                via.dottedDecimalAddress() << ':' << via.port() << ") "
            "to " << 
                dst.dottedDecimalAddress() << ':' << dst.port() << ". "
            "Sent: " << record->outBytes << ", "
            "received: " << record->inBytes;
}
