#include "natfork.ih"

void NatFork::handleChildStatus()
{
    d_pipe.readFrom(STDIN_FILENO);

    int status;
    cin >> status;

    if (status != 0)
        throw Options::FAILED;
}
