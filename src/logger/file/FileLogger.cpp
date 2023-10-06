#include "FileLogger.h"

#include <unordered_map>
#include <ios>
#include <ctime>
#include <iomanip>

const std::string FileLogger::levels[] =
{
    "SERVICE",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG"
};
static const size_t maxlength = 7;

static std::string getTime(void);

FileLogger::FileLogger(std::string filename, Levels limit)
try
    : limit(limit)
{
    if (0 > limit || ALL < limit)
        throw CALL_EX(UnspecifiedLevelILoggerException);

    this->file.open(filename, std::ios::app);
    this->file << '[' << std::setw(maxlength) << std::left << levels[ILogger::SERVICE] << ']'
               << '[' << getTime() << "] Logger started" << std::endl;
}
catch (std::ios::failure &)
{
    throw CALL_EX(UnableToOpenFileLogger);
}

FileLogger::~FileLogger(void)
{
    if (!this->file.is_open())
        return;

    this->file << '[' << std::setw(maxlength) << std::left << levels[ILogger::SERVICE] << ']'
               << '[' << getTime() << "] Logger destroyed" << std::endl;
    this->file.close();
}

void FileLogger::write(Levels level, const std::string message)
{
    if (ALL <= level || 0 > level)
    {
        this->file << '[' << std::setw(maxlength) << std::left << levels[ILogger::SERVICE] << ']'
                   << '[' << getTime() << "] Unspecified log level occured" << std::endl;

        throw CALL_EX(UnspecifiedLevelILoggerException);
    }

    if (this->limit <= level)
        return;

    this->file << '[' << std::setw(maxlength) << std::left << levels[level] << ']'
               << '[' << getTime() << "] " << message << std::endl;
}

static std::string getTime(void)
{
    std::time_t now = std::time(nullptr);
    std::string out = std::asctime(std::localtime(&now));

    return std::string(out.begin(), out.end() - 1);
}

