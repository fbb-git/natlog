#include "record.ih"

ostream &Record::insertInto(std::ostream &out) const
{
    out << d_type << ":\n" 
        "   " << sourceIPstr() << ':' << d_sourcePort << 
            " (via: " << viaIPstr()  << ':' << d_viaPort << ") "
            "to " << destIPstr() << ':' << d_destPort << ";\n"
        "   key: " << d_key.key << "; srcKey: " << srcKey() << 
                                            "; dstKey " << dstKey() << ";\n"
        "   payload: " << d_payload << ", sent: " << d_sentBytes << 
                                    ", received: " << d_receivedBytes << "\n"
        "   from " << beginTime() << " thru " << endTime() <<
    endl;

    return out;
}
