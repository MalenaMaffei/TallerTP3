#include <iostream>
#include <string>
#include "server_ErrorMonitor.h"
using std::cerr;
using std::endl;
#define LISTARMATERIAS "lm"
#define LISTARINSC "li"
#define INS "in"
#define DESINS "de"

void ErrorMonitor::outputError(string error) {
  //    CRITICAL SECTION
  std::lock_guard<std::mutex> lock(m);
  cerr << error << endl;
}

void ErrorMonitor::outputCommand(string user, string command) {
  string command_name;
  if (command == LISTARMATERIAS){
    command_name = "listarMaterias";
  } else if (command == LISTARINSC){
    command_name = "listarInscripciones";
  } else if (command == INS){
//        TODO SACAR PARTE DEL CODIGO
    command_name = "inscribir";
  } else if (command == DESINS){
    command_name = "desinscribir";
  }
  outputError(user + " ejecuta " + command_name + ".");
}

ErrorMonitor::ErrorMonitor() {}
