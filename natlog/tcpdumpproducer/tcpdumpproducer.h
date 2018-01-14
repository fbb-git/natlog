#ifndef INCLUDED_TCPDUMPPRODUCER_
#define INCLUDED_TCPDUMPPRODUCER_

#include <fstream>

#include "../producer/producer.h"
#include "../tcpdumprecord/tcpdumprecord.h"

class Options;
class Storage;

class TcpdumpProducer: public Producer
{
    struct Data
    {
        std::ifstream stream;
        TcpdumpRecord::PktHdr hdr;
        size_t seconds;

        bool before(Data const &other);
    };

    Options &d_options;
    std::ostream &d_stdMsg;
    Storage &d_storage;


    char const *d_inName;
    char const *d_outName;

    Data  d_in;
    Data  d_out;

    char *d_buffer = 0;
    size_t d_bufLen = 0;

    public:
        TcpdumpProducer(std::ostream &stdMsg, Storage &storage);
        ~TcpdumpProducer() override;

    private:
        void run() override;

        void process();

        static void get(Data &data);
        void store(Record::Type, Data &data);
};
        
#endif

