#include "common_Socket.h"
//#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#define SERVER_MODE 0
#define CLIENT_MODE 0


int Socket::filladdrinfo(const char *ip,const char *port, int
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
        if ((bytes_sent=send(
                fD, buffer_ptr, bytes_left, MSG_NOSIGNAL))<=0) {
            return NOK;
        } else {
            buffer_ptr+=bytes_sent;
        }
    }
    return OK;
}

int Socket::BindAndListen(int backlog){
    int s_bind = bind(fD, res->ai_addr, res->ai_addrlen);
    int s_lis = listen(fD, backlog);
    if (s_bind < 0 || s_lis <0){return NOK;}
    return OK;
}

//TODO hacer que devuelva otro socket
int Socket::Accept(Socket &other){
    struct sockaddr_storage c_addr;
    struct sockaddr *a;
    socklen_t *l;
    socklen_t addr_s = sizeof c_addr;

    a = (struct sockaddr *)&c_addr;
    l= &addr_s;

    int new_fd = accept(fD, a, l);
    other.fD = new_fd;
    if (new_fd < 0){ return NOK; }
    return OK;
}

int Socket::Receive(unsigned char *buffer, size_t length){
    int bytes_read = recv(fD, buffer, length, MSG_NOSIGNAL);
    return bytes_read;
}

int Socket::Shutdown(int mode){
    if (mode < 0 || mode > 1){ return NOK; }
    return shutdown(fD, mode);
}

int Socket::socket_destroy(){
    freeaddrinfo(res);
    return close(fD);
}

int Socket::socket_accept_destroy(){
    return close(fD);
}
