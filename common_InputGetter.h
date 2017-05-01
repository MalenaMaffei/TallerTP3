#ifndef TP2_INPUTGETTER_H
#define TP2_INPUTGETTER_H
#include "common_Thread.h"
#include "common_InputQueueMonitor.h"

class InputGetter : public Thread {
 public:
  explicit InputGetter(InputQueueMonitor &queue);
  void run();
 private:
    InputQueueMonitor & queue;
};

#endif //TP2_INPUTGETTER_H
