#ifndef TP2_INPUTMONITOR_H
#define TP2_INPUTMONITOR_H
#include <queue>
#include <string>
using  std::queue;
using std::string;

class InputQueueMonitor {
 public:
  InputQueueMonitor();
  void push(string element);
  string pop();
  bool isQuittingTime() const;
  void setQuittingTime(bool is_quitting_time);
  bool isEmpty();
 private:
  queue<string> inputQueue;
  bool quittingTime;
};

#endif //TP2_INPUTMONITOR_H


#include <queue>
