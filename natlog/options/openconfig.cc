#include "options.ih"

void Options::openConfig()
{
        // the config file is:
        //      - where specified at 'c',   or:
        //      - ~/.natlogrc

    string config;
    if (not d_arg.option(&config, 'c'))
        config = s_defaultConfigPath;

    if (not d_arg.option(&d_PIDfile, 'p'))
        d_PIDfile = s_defaultPIDfile;

    if (access(config.c_str(), R_OK) != 0)
        wmsg << "Configuration file `" << config << "' not found" << endl;
    else
    {
        if (d_verbose)
            cout << "Using configuration file: `" << config << '\'' << endl;
        d_arg.open(config);
    }
}
