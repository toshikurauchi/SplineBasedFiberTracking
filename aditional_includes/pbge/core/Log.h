#ifndef pbge_log
#define pbge_log 1

#include <string>

class Log{
public:
    virtual void write(std::string message) = 0;
    virtual void writeError(std::string message) = 0;
};

class LogTerminal : public Log{
public:
    void write(std::string message);
    void writeError(std::string message);
};

#endif