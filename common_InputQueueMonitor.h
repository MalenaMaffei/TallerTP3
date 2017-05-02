#ifndef TP2_INPUTMONITOR_H
#define TP2_INPUTMONITOR_H
#include <queue>
#include <string>
#include <mutex>
using  std::queue;
using std::string;

class InputQueueMonitor {
 public:
  InputQueueMonitor();
  void push(string element);
  string pop();
  bool isQuittingTime();
  void setQuittingTime(bool is_quitting_time);
  bool isEmpty();
 private:
  void modifyQueue(string &element, int mode);
  std::mutex m;
  queue<string> inputQueue;
  bool quittingTime;
};

#endif //TP2_INPUTMONITOR_H


#include <queue>
