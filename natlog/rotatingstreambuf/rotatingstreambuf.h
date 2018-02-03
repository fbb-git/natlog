#ifndef INCLUDED_ROTATABLESTREAMBUF_
#define INCLUDED_ROTATABLESTREAMBUF_

#include <streambuf>
#include <fstream>
#include <iosfwd>
#include <mutex>

class RotatingStreambuf: public std::streambuf
{
    std::mutex d_mutex;
    bool d_locked = false;
    size_t d_nDays;

    std::ofstream d_out;
    std::string d_name;
  
    int (RotatingStreambuf::*d_overflow)(int ch);
    void (*d_header)(std::ostream &);

    public:
        RotatingStreambuf(size_t nDays, void (*header)(std::ostream &) = 0);
        
        void open(std::string const &name);
    private:
        int overflow(int ch) override;
        int sync() override;

        int unlockedOverflow(int ch);
        int lockedOverflow(int ch);

        static void rotate(RotatingStreambuf *rs);
};

inline RotatingStreambuf::RotatingStreambuf(size_t nDays,
                                            void (*header)(std::ostream &))
:
    d_nDays(nDays),
    d_header(header)
{}
       
#endif
