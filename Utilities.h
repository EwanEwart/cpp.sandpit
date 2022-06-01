#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <time.h>

namespace cc
{
    namespace util
    {
        // date time format: YYYY-MM-DD.HH:mm:ss
        std::string const CurrentDateTime()
        {
            time_t     now = time(NULL);
            struct tm  tstruct;
            char       buf[80];
            localtime_s(&tstruct, &now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
            return buf;
        }

    } // ns util
} // ns cc

#endif
