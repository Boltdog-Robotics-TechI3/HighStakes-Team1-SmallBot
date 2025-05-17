#pragma once
#include <cstdio>

class Logger {
    private:
        bool logToSDCard;
        const char* logFileLocation = "/usd/vexlog.0.log";
        FILE *logFile;
    public:
        ~Logger() {
            if (logFile) fclose(logFile);
        }
        
        Logger(bool logToSD);

        /** Prints a formatted string to the log file.
        * @param format Formatting string, like the regular printf().
        * @remarks can accept any number of items to be formatted in printf
        */
        void Printf(const char* format, ...);

        
        /** Prints a formatted string to the log file, with an endline at the end.
        * @param format Formatting string, like the regular printf().
        * @remarks can accept any number of items to be formatted in printf
        */
        void Printfln(const char* format, ...);
};