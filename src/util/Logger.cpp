#include "utilHeaders/Logger.hpp"
#include <cstdarg>
#include <cstdio>

Logger::Logger(bool logToSD) {
    this->logToSDCard = logToSD;
    if (logToSD) {
        this->logFile = fopen(this->logFileLocation, "a");
    }
}

void Logger::Printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    if (logToSDCard) {
        va_start(args, format);
        vfprintf(logFile, format, args);
        va_end(args);
    }
}

void Logger::Printfln(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\r\n");

    
    if (logToSDCard) {
        va_start(args, format);
        vfprintf(logFile, format, args);
        va_end(args);
        fprintf(logFile, "\r\n");
    }
}