#include "natfork.ih"

extern "C" Producer *allocConntrackProducer(ostream &stdMsg, Storage &storage)
{
    return new ConntrackProducer{ stdMsg, storage };
}
