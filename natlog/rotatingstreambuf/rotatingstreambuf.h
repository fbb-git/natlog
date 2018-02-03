#ifndef INCLUDED_ROTATABLESTREAMBUF_
#define INCLUDED_ROTATABLESTREAMBUF_

#include <streambuf>
#include <fstream>
#include <vector>
#include <iosfwd>
#include <mutex>

class RotatingStreambuf: public std::streambuf
{
    std::mutex d_mutex;
    bool d_locked = false;

    std::ofstream d_out;
    std::string d_name;

    static std::vector<RotatingStreambuf *> s_rotate;
  
    int (RotatingStreambuf::*d_overflow)(int ch);
    void (*d_header)(std::ostream &);

    public:
        RotatingStreambuf(void (*header)(std::ostream &) = 0);
        void open(std::string const &name);

    private:
        int overflow(int ch) override;
        int sync() override;

        int unlockedOverflow(int ch);
        int lockedOverflow(int ch);

        static void rotateThread();
        void rotate(std::string const &suffix);
};

inline RotatingStreambuf::RotatingStreambuf(void (*header)(std::ostream &))
:
    d_header(header)
{}
       
#endif
