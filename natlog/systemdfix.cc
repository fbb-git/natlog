#include "main.ih"

vector<string> systemdFix(int argc, char **argv)
{
    vector<string> vs;

    if (argc == 1 || "-S"s != argv[1])      // no -S: no systemd fuck-up
        return vs;

    vs.push_back(argv[0]);                  // store the program name

    for (int idx = 2; idx != argc; ++idx)   // inspect all args
    {
        string str = argv[idx];

        size_t beg = 0;
        while (true)
        {                                   // check a blank in the argument
            size_t end = str.find_first_of(" \t", beg);
            if (end == string::npos)        // not found: done here
                break;
                                            // pick the part up to the blank
            vs.push_back(str.substr(beg, end - beg));
                                            // and find the 1st char beyond
            beg = str.find_first_not_of(" \t", end);
        }

        vs.push_back(str.substr(beg));      // add the (rest) without blanks
    }

    return vs;
}





