#ifndef INCLUDED_TCP_
#define INCLUDED_TCP_

#include "../ipbase/ipbase.h"

class TCP: public IPbase
{
    enum TCP_type       // see s_tcpIn and 
    {
        TCP_SYN,
        TCP_FIN,
        TCP_SENT,
        TCP_RECVD,
        TCP_IGNORE
    };

    KeyMap d_keyMap;

    static void (TCP::*s_tcpIn[]) (RecordPtr &);

    public:
        TCP(std::ostream &stdMsg, std::ostream &logDataStream);
        ~TCP() override;

    private:
        void inDev(RecordPtr &next)             override;
        void sent(RecordPtr &next)              override;
        void received(RecordPtr &next)    override;

        void outDev(Record const &next)     override;
        void cleanupHook()                  override;

        TCP_type inType(Record const &record);

        void fin(RecordPtr &next);
        void ignore(RecordPtr &next);
        void syn(RecordPtr &next);
};
        
#endif

