#include "utilHeaders/Logger.hpp"
#include "globals.hpp"
#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

#define MAX_LOG_AMOUNT 3

using namespace std;

Logger::Logger(bool logToSD) {
    this->logToSDCard = logToSD;
    if (logToSD) {
        remove(("/usd/vexlog." + to_string(MAX_LOG_AMOUNT) + ".log").c_str());
        struct stat _fileStatus;
        //Move all previous logs up 1 number
        for (int i = MAX_LOG_AMOUNT; i > 0 + 1; i--) {
            string filename = "/usd/vexlog." + to_string(i - 1) + ".log";
            string nextname = "/usd/vexlog." + to_string(i) + ".log";
            //Does the file exist?
            if ((this->logFile = fopen(filename.c_str(), "r"))) {//stat(filename.c_str(), &_fileStatus) == 0) {
                fclose(this->logFile);
                int err = rename(filename.c_str(), nextname.c_str());
                if (err != 0) {
                    print(2, 0, strerror(errno));

                }
            }
        }
        this->logFile = fopen(this->logFileLocation, "w");
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