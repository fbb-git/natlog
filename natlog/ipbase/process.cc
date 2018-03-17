#include "ipbase.ih"

//f: IPbase::process(RecordPtr)
    //c: IPbase::inDev(RecordPtr&)
    //c: TCP::inDev(RecordPtr&)
    //c: IPbase::outDev(Record const&)
    //c: TCP::outDev(Record const&)
    //c: UDP::outDev(Record const&)

void IPbase::process(RecordPtr next)
{
    lock_guard<mutex> lg(d_mutex);

    switch (next->type())
    {
        case Record::IN:
            inDev(next);
        break;

        case Record::OUT:
            outDev(next);
        break;

        case Record::NEW:
            insert(next);
        break;

        case Record::DESTROY:
            destroy(*next);
        break;
    }
}



