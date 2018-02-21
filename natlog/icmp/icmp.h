#ifndef INCLUDED_ICMP_
#define INCLUDED_ICMP_

#include "../ipbase/ipbase.h"

class ICMP: public IPbase
{
    public:
        ICMP(std::ostream &stdMsg, std::ostream &logDataStream);

    private:
        void destroy(Record const *record)              override;
        void outDev(Record const *next)                 override;
        void logConnection(Record const *record) const  override;
};
        
#endif
