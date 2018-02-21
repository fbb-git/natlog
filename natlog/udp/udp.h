#ifndef INCLUDED_UDP_
#define INCLUDED_UDP_

#include "../ipbase/ipbase.h"

class UDP: public IPbase
{
    public:
        UDP(std::ostream &stdMsg, std::ostream &logDataStream);

    private:
        void outDev(Record const *next) override;

};
        
#endif
