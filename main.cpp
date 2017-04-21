#include "client.cpp"
#include "server.cpp"

int main(int argc, char **argv){
    if (argc < 2){ return 0;}
    string mode = argv[1];

    string server_mode = "server";
    string client_mode = "client";

    if (mode == client_mode){
//        char *server_ip = argv[2];
//        char *server_port = argv[3];
//        char *file_name = argv[4];
        client("127.0.0.1", "8080");
    } else if (mode == server_mode){
//        char *server_port = argv[2];
        server("8080");
    }
    return 0;
}