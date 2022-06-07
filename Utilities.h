#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <time.h>
#include <cstdio>

namespace cc
{
    namespace util
    {
        // date time format: YYYY-MM-DD.HH:mm:ss
        std::string const CurrentDateTime()
        {

            time_t     now = time(nullptr);
            struct tm  tmstruct;

#if defined(_WIN32) || defined(_WIN64)
            /*
                        _Check_return_wat_
                        static __inline errno_t __CRTDECL localtime_s(
                            _Out_ struct tm*    const _Tm,
                            _In_  time_t const* const _Time
                            )
                        {
                            return _localtime64_s(_Tm, _Time);
                        }

            */
            localtime_s(&tmstruct, &now);
#elif defined(__linux__)
            // tmstruct = localtime(&now);
            localtime_s(&now, &tmstruct);
#endif
            char       buf[80];
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tmstruct);

            return buf;
        }
    } // ns util
} // ns cc

#endif
