#include "common_InputGetter.h"
#include <iostream>
#include <string>

InputGetter::InputGetter(InputQueueMonitor &queue) : queue(queue) {}
void InputGetter::run() {
    string input;
    while (getline(std::cin, input)){
        queue.push(input);
//        TODO esto es necesario?
        if (input == "q"){ break; }
    }
    queue.setQuittingTime(true);
}
