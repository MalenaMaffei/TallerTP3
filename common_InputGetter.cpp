#include "common_InputGetter.h"
#include <iostream>
#include <string>

InputGetter::InputGetter(InputQueueMonitor &queue) : queue(queue) {}
void InputGetter::run() {
    string input;
    while (getline(std::cin, input)){
//        std::cout << "hubo input: "<<input << std::endl;

        queue.push(input);
        if (input == "q"){ break; }
    }
    queue.setQuittingTime(true);
}
