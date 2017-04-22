#ifndef PROJECT_SOCKET_H
#define PROJECT_SOCKET_H

#include <netdb.h>

#define OK 0
#define NOK -1
#define NO_IP 0
#define MSG_NO_SIGNAL 0

class Socket {
private:
    int fD;
    struct addrinfo *res;
    int filladdrinfo(const char *ip,const char *port, int
    mode);

public:
//TODO Hacer excepciones para todo esto
//Inicializa un socket con su FD usando la estructura addrinfo
    int Create(const char *ip, const char *port, int mode);

//Conecta un socket usando la estructura pasada.
// Devuelve OK o NOK si hay error.
//PRE: el socket fue inicializado usando Create
    int Connect(struct sockaddr *addr, socklen_t addrlen);

//Crea un socket con su FD usando la estructura addrinfo y luego lo conecta
//Hace la conexión iterando sobre addr
// Devuelve OK o NOK si hay error.
    int CreateAndConnect(const char *ip, const char *port);

//Hace un bind y luego un listen con el socket pasado.
// Devuelve OK o NOK si hay error.
//PRE: el socket fue inicializado usando Create
    int BindAndListen(int backlog);

//Acepta la conexion que se intenta hacer al puerto en la estructura a
//Crea un nuevo socket para comunicarse con ese puerto.
// Devuelve OK o NOK si hay error.
//PRE: self fue inicializado con Create.
//Se llamo a BindAndListen con self.
//TODO VER COMO DEVOLVER OTRO SOCKET
    int Accept(Socket &other);

//Envia la cantidad length de bytes de source.
// Devuelve OK o NOK si hay error.
//PRE: length es del largo apropiado.
//self fue inicializado y conectado o creado con Accept.
    int Send(unsigned char *source, size_t length);

//Recibe hasta length bytes y los guarda en buffer.
// Devuelve bytes recibidos o NOK si hay error.
//PRE: length es del largo apropiado.
//self fue inicializado y conectado o creado con Accept.
    int Receive(unsigned char *buffer, size_t length);

//Realiza un shutdown en el modo indicado sobre el socket
// Devuelve OK o NOK si hay error.
//PRE: el socket fue inicializado usando Create
    int Shutdown(int mode);

//Destruye la instancia self liberando sus recursos.
//Cierra el socket y libera a struct addrinfo res.
// PRE: self fue inicializado mediante Create
//TODO que onda aca? herencia?
    int Destroy();

//Destruye un socket accept liberando sus recursos.
//Cierra el socket.
// PRE: self fue inicializado mediante Accept
    int accept_destroy();
};


#endif //PROJECT_SOCKET_H
