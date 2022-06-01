#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>

using namespace std;

#define LOGGER cc::logger::SimpleLogger::GetLogger()

/*
    SimpleLogger
*/
namespace cc
{
    namespace logger
    {
        class SimpleLogger
        {
        public:
            void Log(std::string const& sMessage);
            void Log(char const* format, ...);
            SimpleLogger& operator<<(string const& sMessage);
            static SimpleLogger* GetLogger();
        private:
            SimpleLogger();
            SimpleLogger(SimpleLogger const&) {};
            SimpleLogger& operator=(SimpleLogger const&)
            {
                return *this;
            };
            static  std::string const m_sFileName;
            static SimpleLogger* m_pThis;
            static ofstream m_Logfile;
        };
    } // ns logger
} // ns cc
#endif
