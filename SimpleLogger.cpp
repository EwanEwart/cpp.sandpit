#include "SimpleLogger.h"
#include"Utilities.h"

namespace cc
{
    namespace logger
    {
        const string SimpleLogger::m_sFileName{ "SimpleLogger.log" };
        SimpleLogger* SimpleLogger::m_pThis{ nullptr };
        ofstream SimpleLogger::m_Logfile;
        SimpleLogger::SimpleLogger() { }
        SimpleLogger* SimpleLogger::GetLogger()
        {
            if (m_pThis == nullptr)
            {
                m_pThis = new SimpleLogger();
                m_Logfile.open(m_sFileName.c_str(), ios::out | ios::app);
            }
            return m_pThis;
        }

        void SimpleLogger::Log(char const* format, ...)
        {
            char* sMessage = nullptr;
            int nLength = 0;
            va_list args;
            va_start(args, format);

#if defined(_WIN32) || defined(_WIN64)
            // Returns the number of characters in the formatted string using a pointer to a list of arguments.
            nLength = _vscprintf(format, args) + 1;// \0 not counted => +1
#elif defined(__linux__)
            FILE* fp = fopen("/dev/null", "w");
            nLength = vfprintf(fp, format, args) + 1;// \0 not counted => +1
#else
            puts("Operating system not supported.\n")
            exit(-1);
#endif
            sMessage = new char[nLength];

#if defined(_WIN32) || defined(_WIN64)
            vsprintf_s(sMessage, nLength, format, args);
#elif defined(__linux__)
            vsnprintf(sMessage, nLength, format, args);
#else
            puts("Operating system not supported.\n");
            exit(-1);
#endif

            m_Logfile << cc::util::CurrentDateTime() << ":\n";
            m_Logfile << sMessage << "\n";

            va_end(args);

            delete[] sMessage;
        }   // void SimpleLogger::Log(char const* format, ...)

        void SimpleLogger::Log(string const& sMessage)
        {
            m_Logfile << cc::util::CurrentDateTime() << ":\n";
            m_Logfile << sMessage << "\n";
        }

        SimpleLogger& SimpleLogger::operator<<(string const& sMessage)
        {
            m_Logfile << "\n" << cc::util::CurrentDateTime() << ":\n";
            m_Logfile << sMessage << "\n";
            return *this;
        }
    } // ns logger
} // ns cc
