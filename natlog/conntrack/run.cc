#include "conntrack.ih"

void Conntrack::run()
{
    Signal::instance().add(SIGTERM, *this);

    d_parent << 0 << endl;                    // all OK

    d_stdMsg << "starting: using " << d_options.conntrackCommand() << endl;
    fork();
}








