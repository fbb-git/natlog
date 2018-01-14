#include "conntrackproducer.ih"

void ConntrackProducer::run()
{
    size_t max = d_options.conntrackRestart();
    d_stdMsg << "starting `" << d_options.conntrackCommand() << 
                "' (max " << max << " restarts)" << endl;

    ++max;      // restarts, so add 1 for initial startup.

    for (size_t idx = 0; idx != max; )
    {
        ++idx;

        try
        {
            d_pipe = Pipe();
            fork();
            return;
        }
        catch (Options::ExitStatus status)
        {
            d_stdMsg << "conntrack run " << idx << " ended" << endl;
        }
    }
    d_stdMsg << "conntrack started " << max << " times, giving up" << endl;
}








