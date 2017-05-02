#include "common_Socket.h"
// #define _POSIX_C_SOURCE 200112L
#include "common_SocketException.h"
// #include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory.h>
// #include <stdio.h>
#include "common_SocketException.h"
// #include <stdexcept>
#include <cstring>
#include <string>
// #include <errno.h>
#include <fcntl.h>
#define SERVER_MODE 0
#define CLIENT_MODE 0

#define BUFFSIZE 300
int Socket::filladdrinfo(const char *ip, const char *port, int
mode){
    int status = 0;

    struct addrinfo hints;
//    struct addrinfo *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (mode == SERVER_MODE){
        hints.ai_flags = AI_PASSIVE;
    } else{
        hints.ai_flags = 0;
    }

    status = getaddrinfo(ip, port, &hints, &res);
    if (status < 0) { return (NOK); }
    if (!res) { return NOK; }
//    res = res;
    return OK;
}

int Socket::Create(const char *ip, const char *port, int mode){
    int skt = 0;
    filladdrinfo(ip, port, mode);
    skt = socket(res->ai_family, res->ai_socktype,
                 res->ai_protocol);
    fD = skt;
    return skt;
}

int Socket::CreateAndConnect(const char *ip, const char *port){
    struct addrinfo* ptr;
    bool connected = false;
    int status = 0;
    int skt = 0;

    filladdrinfo(ip, port, CLIENT_MODE);

    for (ptr = res; ptr != NULL && connected == false;
         ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (skt == NOK) {
            return NOK;
        } else {
            fD = skt;
            status = connect(fD,  ptr->ai_addr, ptr->ai_addrlen);
            if (status == NOK) {
                close(skt);
                return NOK;
            }
            connected = (status != NOK);
        }
    }

    fD = skt;
    return OK;
}

int Socket::Send(unsigned char *source, size_t length){
    int bytes_left;
    int bytes_sent = 0;
    unsigned char *buffer_ptr = source;
    for (bytes_left = length; bytes_left>0; bytes_left-=bytes_sent) {
        if (!isConnected()) {
            throw SocketException("Intentaba mandar pero se cerro el socket");
        }
        bytes_sent=send(fD, buffer_ptr, bytes_left, MSG_NO_SIGNAL);
        if (bytes_sent<=0) {
            return NOK;
        } else {
            buffer_ptr+=bytes_sent;
        }
    }
    return OK;
}

int Socket::BindAndListen(int backlog){
    int s_bind = bind(fD, res->ai_addr, res->ai_addrlen);
    if (s_bind < 0){ throw SocketException("error en bind"); }
    int s_lis = listen(fD, backlog);
    if (s_lis <0){ throw SocketException("error en listen"); }
    return OK;
}

Socket Socket::Accept() const{
    Socket other;
    struct sockaddr_storage c_addr;
    struct sockaddr *a;
    socklen_t *l;
    socklen_t addr_s = sizeof c_addr;

    a = (struct sockaddr *)&c_addr;
    l= &addr_s;

    int new_fd = accept(fD, a, l);
    other.fD = new_fd;
    if (new_fd < 0){
        throw SocketException("Error en Accept nro: " + std::to_string(errno));
    }
    return other;
}

int Socket::Receive(unsigned char *buffer, size_t length){
    int bytes_read = recv(fD, buffer, length, MSG_NO_SIGNAL);
    if (bytes_read == MSG_NO_SIGNAL){
        throw SocketException("Intentaba recibir pero se cerro el socket");
    }
    return bytes_read;
}

int Socket::Shutdown(int mode){
    if (mode < 0 || mode > 1){ return NOK; }
    return shutdown(fD, mode);
}

int Socket::Destroy(){
    freeaddrinfo(res);
    return close(fD);
}

int Socket::accept_destroy(){
    return close(fD);
}
string Socket::ReceiveStrWLen(int lenSize) {
    int read = 0;
    unsigned char buffer_leer[BUFFSIZE] = {0};
    while (read < lenSize){
        read = Receive(buffer_leer,lenSize);
    }

    int net_length;
    std::memcpy(&net_length, buffer_leer, sizeof net_length);

    int normal_length = ntohl(net_length);
    int bytes_read = 0;

    while (bytes_read < normal_length){
//        TODO mover puntero hasta llenar
        bytes_read += Receive(buffer_leer,BUFFSIZE);
    }
    buffer_leer[bytes_read] = '\0';
    string received((char *)buffer_leer);
    return received;
}

void Socket::SendStrWLen(string &str, int lenSize) {
    int normal_length = str.size();
    int net_length = htonl(normal_length);
    Send((unsigned char*)&net_length, lenSize);
    char *char_message = &str[0];
    Send((unsigned char *)char_message, str.size());
}

bool Socket::isConnected() {
    int read = recv(fD, NULL, 0, MSG_DONTWAIT | MSG_PEEK);
    return read != 0;
}

int Socket::getFD() const {
    return fD;
}
void Socket::setToNonBlocking() {
    if (fcntl(fD, F_SETFL, fcntl(fD, F_GETFL, 0) | O_NONBLOCK) == -1){
        throw SocketException("error en setear nonblock");
    }
}
