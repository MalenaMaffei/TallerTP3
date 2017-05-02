#include "common_InputQueueMonitor.h"
#include <string>
#include <iostream>
#define PUSH 1
#define POP -1

InputQueueMonitor::InputQueueMonitor() {
    quittingTime = false;
}

void InputQueueMonitor::push(string element) {
//    std::lock_guard<std::mutex> lock(m);
    modifyQueue(element, PUSH);
//    inputQueue.push(element);
}

string InputQueueMonitor::pop() {
//    std::lock_guard<std::mutex> lock(m);
    if (inputQueue.size() == 0){
        return "";
    }
//    string element = inputQueue.front();
//    inputQueue.pop();
    string element;
    modifyQueue(element, POP);
    return element;
}

bool InputQueueMonitor::isQuittingTime() {
    return quittingTime;
}

void InputQueueMonitor::setQuittingTime(bool is_quitting_time) {
    std::lock_guard<std::mutex> lock(m);
    InputQueueMonitor::quittingTime = is_quitting_time;
}

bool InputQueueMonitor::isEmpty() {
    return inputQueue.empty();
}
void InputQueueMonitor::modifyQueue(string &element, int mode) {
    std::lock_guard<std::mutex> lock(m);
    if (mode == PUSH){
//        std::cout << "pushing: " << element << std::endl;
        inputQueue.push(element);
    } else {
        element = inputQueue.front();
//        std::cout << "poping: " << element << std::endl;
        inputQueue.pop();
    }
}
