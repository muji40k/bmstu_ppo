#ifndef _FILELOGGER_H_
#define _FILELOGGER_H_

#include <fstream>

#include "ILogger.h"

class FileLogger : public ILogger
{
    public:
        FileLogger(std::string filename, Levels limit=ALL);
        virtual ~FileLogger(void) override;
        virtual void write(Levels level, const std::string message) override;

    private:
        const Levels limit;
        std::ofstream file;

        static const std::string levels[];
};

DEF_EX(CommonFileLogger, CommonILoggerException, "Common FileLogger Exception");
DEF_EX(UnableToOpenFileLogger, CommonFileLogger, "Unable to open log file");

#endif

