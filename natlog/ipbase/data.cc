#include "ipbase.ih"

pair<char const *, char const *> IPbase::s_logTypeText[]
{
    { "",               "ok"         },
    { " (INCOMPLETE)",  "incomplete" },
    { " (EOP)",         "eop"        }
};

IPbase::LogType IPbase::s_logType = IPbase::COMPLETE;
