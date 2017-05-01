#include "common_InputQueueMonitor.h"
#include <string>
InputQueueMonitor::InputQueueMonitor() {
    quittingTime = false;
}

void InputQueueMonitor::push(string element) {
    inputQueue.push(element);
}

string InputQueueMonitor::pop() {
    if (inputQueue.size() == 0){
        return "";
    }
    string element = inputQueue.front();
    inputQueue.pop();
    return element;
}
bool InputQueueMonitor::isQuittingTime() const {
    return quittingTime;
}
void InputQueueMonitor::setQuittingTime(bool is_quitting_time) {
    InputQueueMonitor::quittingTime = is_quitting_time;
}
bool InputQueueMonitor::isEmpty() {
    return inputQueue.empty();
}
