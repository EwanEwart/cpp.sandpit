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
            nLength = _vscprintf(format, args) + 1;// \0 not counted => +1
            sMessage = new char[nLength];
            vsprintf_s(sMessage, nLength, format, args);
            m_Logfile << cc::util::CurrentDateTime() << ":\n";
            m_Logfile << sMessage << "\n";
            va_end(args);

            delete[] sMessage;
        }

        void SimpleLogger::Log(string const& sMessage)
        {
            m_Logfile << cc::util::CurrentDateTime() << ":\n";
            m_Logfile << sMessage << "\n";
        }

        SimpleLogger& SimpleLogger::operator<<( string const& sMessage)
        {
            m_Logfile << "\n" << cc::util::CurrentDateTime() << ":\n";
            m_Logfile << sMessage << "\n";
            return *this;
        }
    } // ns logger
} // ns cc
