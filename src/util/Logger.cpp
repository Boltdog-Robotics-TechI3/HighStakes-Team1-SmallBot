#include "utilHeaders/Logger.hpp"
#include "globals.hpp"
#include "liblvgl/llemu.hpp"
#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

#define MAX_LOG_AMOUNT 3

using namespace std;

/** Because renaming doesn't work, this file is used instead.
* @param og File to copy from
* @param destination File to copy file to. Does not have to already exist. If it does it will be overwritten.
*/
bool copyFile(const char* og, const char* destination) {
    bool sucess = false;
    FILE *ogFile = fopen(og, "r");
    FILE *destFile = fopen(destination, "w");

    if (ogFile == NULL || destFile == NULL) {
        //Ideally, we would have error logging here.
        goto close;
    }
    int c;
    while ((c = fgetc(ogFile)) != EOF)
    {
        fputc(c, destFile);
    }
    sucess = true;

    close:
        fclose(ogFile);
        fclose(destFile);
        return sucess;
}

Logger::Logger(bool logToSD) {
    this->logToSDCard = logToSD;
    if (logToSD) {
        struct stat _fileStatus;
        //Move all previous logs up 1 number
        for (int i = MAX_LOG_AMOUNT; i > 0; i--) {
            string filename = "/usd/vexlog." + to_string(i - 1) + ".log";
            string nextname = "/usd/vexlog." + to_string(i) + ".log";
            //Does the file exist?
            if ((this->logFile = fopen(filename.c_str(), "r"))) {//stat(filename.c_str(), &_fileStatus) == 0) {
                fclose(this->logFile);
                bool suc = copyFile(filename.c_str(), nextname.c_str());
                // if (!suc) {
                //     pros::lcd::set_text(5, strerror(errno));
                // }
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