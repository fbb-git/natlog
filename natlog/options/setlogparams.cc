#include "options.ih"

void Options::setLogParams()
{
    string value;

    if (not d_arg.option(&d_log, "log"))     
    {
        d_log = "syslog";
        if (not d_arg.option(&d_syslogTag, "syslog-tag"))
            d_syslogTag = s_defaultSyslogIdent;
    
        setSyslogFacility();
        setSyslogPriority();
    }
    else if (d_log == "off")                    // no logging
        d_log.clear();

    d_arg.option(&d_logData, "log-data");
//    {
//        if (d_arg.option(&value, "log-data-flush"))
//            d_logDataFlush = max(1LU, stoul(value));
//    }

    if (d_arg.option(&value, "log-rotate"))     // log file rotation in days
    {
        istringstream in{ value };

        in >> d_rotateFreq;
        switch (in.get())
        {
            case 'd':
                d_rotateFactor = 24 * 60;
                d_rotateTimeSpec = " days";
            break;

            case 'h':
                d_rotateFactor = 60;
                d_rotateTimeSpec = " hours";
            break;

            case 'm':
                d_rotateTimeSpec = " minutes";
            break;

            default:
            throw Exception{} << "`log-rotate " << value << "' not supported";
        }

        if (d_rotateFreq == 1)
            d_rotateTimeSpec.pop_back();

        if (isdigit(in.peek()))
             in >> d_nRotations;
        else if (in.peek() == EOF)
            d_nRotations = 1;
        else
            throw Exception{} << "`--log-rotate " << value << 
                                                    "' not supported";
    }
}







