#include "options.ih"

void Options::openConfig()
{
        // the config file is:
        //      - where specified at 'c',   or:
        //      - ~/.natlogrc

    if (not d_arg.option(&d_configPath, 'c'))
        d_configPath = s_defaultConfigPath;

    if (access(d_configPath.c_str(), R_OK) == 0)
        d_arg.open(d_configPath);

    if (not d_arg.option(&d_PIDfile, 'p'))
        d_PIDfile = s_defaultPIDfile;
}



