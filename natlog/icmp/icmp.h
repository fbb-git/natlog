#ifndef INCLUDED_ICMP_
#define INCLUDED_ICMP_

#include "../ipbase/ipbase.h"

class ICMP: public IPbase
{
    public:
        ICMP(std::ostream &stdMsg, std::ostream &logDataStream);
        ~ICMP() override;

    private:
        void logConnection(Record const &record) const  override;

        void sent(RecordPtr &next)          override;
        void received(RecordPtr &next)      override;
        void outDev(RecordPtr &next)        override;
};
        
#endif
