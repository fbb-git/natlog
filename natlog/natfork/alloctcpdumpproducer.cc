#include "natfork.ih"

extern "C" Producer *allocTcpdumpProducer(ostream &stdMsg, Storage &storage)
{
    return new TcpdumpProducer{ stdMsg, storage };
}
