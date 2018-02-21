#ifndef INCLUDED_ICMP_
#define INCLUDED_ICMP_

#include "../ipbase/ipbase.h"

class ICMP: public IPbase
{
    public:
        ICMP(std::ostream &stdMsg, std::ostream &logDataStream);

    private:
        void logConnection(Record const *record) const  override;

        void sent(Record *next)     override;
        void received(Record *next)     override;
        void outDev(Record const *next) override;
};
        
#endif
