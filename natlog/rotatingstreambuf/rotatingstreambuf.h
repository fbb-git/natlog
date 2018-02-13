#ifndef INCLUDED_ROTATABLESTREAMBUF_
#define INCLUDED_ROTATABLESTREAMBUF_

#include <streambuf>
#include <fstream>
#include <vector>
#include <iosfwd>
#include <thread>
#include <bobcat/semaphore>

class RotatingStreambuf: public std::streambuf
{
    std::mutex d_mutex;
    bool d_locked = false;
    volatile bool d_contents = false;

    std::ofstream d_out;
    std::string d_name;

    int (RotatingStreambuf::*d_overflow)(int ch);
    void (*d_header)(std::ostream &);

    static std::vector<RotatingStreambuf *> s_rotate;
    static FBB::Semaphore s_semaphore;
    static std::thread s_rotateThread;
  
    public:
        RotatingStreambuf(void (*header)(std::ostream &) = 0);
        void open(std::string const &name);
        static void notify();

        static void startThread();

    private:
        int overflow(int ch) override;
        int sync() override;

        int unlockedOverflow(int ch);
        int lockedOverflow(int ch);

        static void rotateThread();
        void rotate(size_t nFiles);
};

inline RotatingStreambuf::RotatingStreambuf(void (*header)(std::ostream &))
:
    d_header(header)
{}

#endif
