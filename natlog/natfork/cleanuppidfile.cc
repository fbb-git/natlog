#include "natfork.ih"

void NatFork::cleanupPidFile() const    // called by childProcess
{
    ifstream pidFile(d_options.pidFile());
    pid_t pid;

    if (pidFile >> pid && pid == getpid())
    {
        pidFile.close();
        unlink(d_options.pidFile().c_str());
    }
}
