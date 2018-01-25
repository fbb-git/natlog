#include "tcpdumpproducer.ih"

void TcpdumpProducer::process()
{
    while (d_in.stream.good() || d_out.stream.good())
    {
        if (d_in.before(d_out))
            store(Record::IN, d_in);

        else if (d_out.before(d_in))
            store(Record::OUT, d_out);

        else
        {
            store(Record::IN, d_in);
            store(Record::OUT, d_out);
        }
    }
}

