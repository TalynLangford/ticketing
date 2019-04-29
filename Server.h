#pragma once
#include "IService.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <future>

class Server {

public:
    Server();
    Server(int port, int backlog, int maxlines);
    ~Server();

    bool startServer(IService &service);

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
    void listenServer(ServerDeps deps, IService &s);
    static void handleConnection(int fd, int addrlen, int max_lines, IService &service);
};