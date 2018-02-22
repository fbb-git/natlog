#include "ipbase.ih"

//static size_t count = 0;

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



