#include "ipbase.ih"

pair<char const *, char const *> IPbase::s_logTypeText[]
{
    { "",               "ok"         },
    { " (EXPIRED)",  "expired" },
    { " (EOP)",         "eop"        }
};

IPbase::LogType IPbase::s_logType = IPbase::COMPLETE;
