#include "natfork.ih"

void NatFork::checkSyslogParam(char const *label, 
                               string const &actual, string const &err)
{
    if (err.length())
        d_stdMsg << "[Warning] using syslog " << label << '`' <<
                actual << "', ignoring unsupported " << label << '`' << endl;
}
