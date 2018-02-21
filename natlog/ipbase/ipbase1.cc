#include "ipbase.ih"

IPbase::IPbase(std::ostream &stdMsg, std::ostream &logDataStream)
:
    d_stdMsg(stdMsg),
    d_logDataStream(logDataStream) 
{
    string path;
    d_logData = 
        ArgConfig::instance().option(&path, "log-data") == 0 ?
            &IPbase::noDataLog
        :
            &IPbase::logData;
}
