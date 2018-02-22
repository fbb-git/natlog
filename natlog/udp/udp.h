#ifndef INCLUDED_UDP_
#define INCLUDED_UDP_

#include "../ipbase/ipbase.h"

class UDP: public IPbase
{
    KeyMap d_keyMap;

    public:
        UDP(std::ostream &stdMsg, std::ostream &logDataStream);

    private:
        void sent(Record *next) override;
        void received(Record *next) override;
        void outDev(Record const *next) override;

};
        
#endif
