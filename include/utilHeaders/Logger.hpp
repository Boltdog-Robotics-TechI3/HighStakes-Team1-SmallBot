#pragma once
#include <cstdio>

class Logger {
    private:
        bool logToSDCard;
        const char* logFileLocation = "/usd/lastlog.log";
        FILE *logFile;
    public:
        ~Logger() {
            if (logFile) fclose(logFile);
        }
        
        Logger(bool logToSD);

        void Printf(const char* format, ...);
        void Printfln(const char* format, ...);
};