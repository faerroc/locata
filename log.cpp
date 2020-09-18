#include "log.h"

Log::LEVEL Log::level = Log::NONE;
FILE *Log::file = stderr;

Log::Log()
{}

void Log::setLogLevel(LEVEL lvl)
{
    level = lvl;
}

void Log::setLogFile(FILE *f)
{
    file = f;
}

void Log::log(LEVEL lvl, const char *args, ...)
{
    va_list argp;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    unsigned long long millisecondsSinceEpoch =
    (unsigned long long)(tv.tv_sec) * 1000 +
    (unsigned long long)(tv.tv_usec) / 1000;

    if(lvl & level)
    {
		fprintf(file, "%llu " , millisecondsSinceEpoch);
	}

    va_start(argp, args);
    if(lvl & level)
    {
        vfprintf(file, args, argp);
    }
    va_end(argp);
}

void Log::logArray(LEVEL lvl, char *buff, int len)
{
    if(lvl & level)
    {
        for(int i = 0; i < len; i++)
        {
            fprintf(file, "%02x ", buff[i]);
        }
        fprintf(file, "\n");
    }
}
