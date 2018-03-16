#include "natfork.ih"

extern "C" Producer *allocDevicesProducer(ostream &stdMsg, Storage &storage)
{
    return new DevicesProducer{ stdMsg, storage };
}
