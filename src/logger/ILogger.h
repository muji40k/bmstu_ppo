#ifndef _ILOGGER_H_
#define _ILOGGER_H_

#include <string>

#include "logger_exception.h"

class ILogger
{
    public:
        using Levels = enum
        {
            SERVICE,
            ERROR,
            WARNING,
            INFO,
            DEBUG,
            ALL
        };

    public:
        virtual ~ILogger(void) = default;
        virtual void write(Levels level, const std::string message) = 0;
};

DEF_EX(CommonILoggerException, LoggerException, "Common ILogger Exception");
DEF_EX(UnspecifiedLevelILoggerException, CommonILoggerException, "Level is unsupported");

#endif

