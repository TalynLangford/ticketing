#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

class Server {

public:
    Server();
    Server(int port, int backlog, int maxlines);
    ~Server();

    bool startServer();

private:
    struct ServerDeps {
        int fd;
        sockaddr_in address;
    };

    int m_port;
    int m_backlog;
    int m_maxLines;
    const char* m_exitMsg = "exit";

    ServerDeps configureServer();
    void bindServer(ServerDeps deps);
    void listenServer(ServerDeps deps);
};