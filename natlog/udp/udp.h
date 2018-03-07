#ifndef INCLUDED_UDP_
#define INCLUDED_UDP_

#include "../ipbase/ipbase.h"

class UDP: public IPbase
{
    KeyMap d_keyMap;

    public:
        UDP(std::ostream &stdMsg, std::ostream &logDataStream);
        ~UDP() override;

    private:
        void sent(RecordPtr &next)          override;
        void received(RecordPtr &next)      override;
        void outDev(Record const &next)     override;
        void cleanupHook()                  override;

};
        
#endif
