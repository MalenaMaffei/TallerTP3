#ifndef TP2_SERVER_H
#define TP2_SERVER_H
#include <string>
#include "common_Thread.h"
#include "common_Socket.h"
class Server: public Thread {
 public:
  Server(const string &port,const string &usuariosFile,
         const string &materiasFile);
  void run();
  virtual ~Server();
  void shutdown();

 private:
  bool exit;
  Socket acceptSocket;
  string port;
  string usuariosFile;
  string materiasFile;
};

#endif //TP2_SERVER_H
