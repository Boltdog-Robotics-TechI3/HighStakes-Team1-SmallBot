#include "main.h"
#include <queue>
#include <string>

// Controllers
pros::Controller driverController(pros::E_CONTROLLER_MASTER);
struct PrintMessage {
    int line;
    int col;
    std::string text;
};
std::queue<PrintMessage> printQueue;

/**
* Task that prints messages to the controller screen. 
*/
void printMessages(void* param) {
    pros::Task::notify_take(true, TIMEOUT_MAX);
    driverController.clear();
    while (true) {
        if (!printQueue.empty()) {
            PrintMessage message = printQueue.front();
            driverController.set_text(message.line, message.col, message.text);
            printQueue.pop();
        }
        pros::delay(50);
    }
}

/**
* Sends a message to the print queue to be printed on the controller screen.
*
* @param line the line to print the message on
* @param col the column to print the message on
* @param text the message to print 
*/
void print(int line, int col, std::string text) {
    // If the message is the same as the last message, don't print it
    if (!printQueue.empty() && printQueue.back().text.compare(text) == 0) {
        return;
    }

    // If the queue is too long, pop the oldest message
    if (printQueue.size() > 200) {
        printQueue.pop();
    }
    printQueue.push({line, col, text});
}