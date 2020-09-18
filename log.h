#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

class Log
{
public:
    Log();

    enum LEVEL {NONE = 0x00, ERROR = 0x01, WARN = 0x03, TRACE = 0x07, DEBUG = 0x0F, ALL= 0xFF};

    static void setLogLevel(LEVEL lvl);
    static void setLogFile(FILE *f);

    static void log(LEVEL lvl, const char* args, ...);
    static void logArray(LEVEL lvl, char *buff, int len);

private:
    static LEVEL level;
    static FILE *file;
};
