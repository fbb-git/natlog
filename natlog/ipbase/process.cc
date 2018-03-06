#include "ipbase.ih"

//static size_t count = 0;

//f: IPbase::process(Record*)
    //c: IPbase::inDev(Record*)
    //c: TCP::inDev(Record*)
    //c: IPbase::outDev(Record*)
    //c: TCP::outDev(Record*)
    //c: UDP::outDev(Record*)

void IPbase::process(Record *next)
{
    lock_guard<mutex> lg(d_mutex);

//CERR << next->protocolStr() << ' ' << ++count << '\n';

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
            destroy(next);
        break;
    }
}



