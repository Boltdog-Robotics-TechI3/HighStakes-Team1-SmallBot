#pragma once
#include <cstdio>
#include <string>
#include <vector>
#include "/utilHeaders/Logger.hpp"

using namespace std;

class CSVFile {
    Logger* _logger;
    int width;
    /** Create a CSV File Logger
    * @param filename Name of the csv file
    * @param headers Name of each column. Length determines the amount of rows in the CSV.
    */
    CSVFile(std::string filename, std::vector<const char*> headers) {
        _logger = new Logger(filename, true);
        width = headers.size();
        printData(headers);
    }

    void printData(std::vector<const char*> data) {
        string value = "";
        for (int i = 0; i < data.size(); i++) {
            value += data[i];
            value += ",";
        }
        _logger->Printfln(value.c_str());
    }
};