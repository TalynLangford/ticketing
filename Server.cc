#include "Server.h"

Server::Server() : m_port(5432), m_backlog(10), m_maxLines(1024) {}
Server::Server(int m_port, int m_backlog, int m_maxLines) : m_port(m_port), m_backlog(m_backlog), m_maxLines(m_maxLines) {}
Server::~Server() {}

bool Server::startServer()
{
    ServerDeps deps = configureServer();
    bindServer(deps);
    listenServer(deps);
}

Server::ServerDeps Server::configureServer()
{
    ServerDeps deps;
    int fd;
    struct sockaddr_in address;
    int opt = 1;
    
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        perror("socket failed");
        exit(1);
    }

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(m_port);

    deps.fd = fd;
    deps.address = address;
    
    return deps;
}

void Server::bindServer(Server::ServerDeps deps)
{
    if (bind(deps.fd, (struct sockaddr*)&deps.address, sizeof(deps.address)) < 0)
    {
        perror("bind error");
        exit(1);
    }
}

void Server::listenServer(Server::ServerDeps deps)
{
    int new_s, valread;
    int addrlen = sizeof(deps.address);
    char buf[m_maxLines] = {0};
    char const *msg = "Hello from the server";

    if (listen(deps.fd, m_backlog) < 0)
    {
        perror("listen");
        exit(1);
    }

    std::cout << "listening..." << std::endl;

    if ((new_s = accept(deps.fd, (struct sockaddr*)&deps.address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(1);
    }

    std::cout << "accepted..." << new_s << std::endl;

    while(1)
    {
        // truncates long messages. Use recv in while to capture.
        valread = read(new_s, buf, m_maxLines);

        std::cout << "read : " << valread << std::endl;
        if (valread < 0)
        {
            perror("valread");
        }
        printf("%s\n",buf);
        send(new_s, msg, strlen(msg), 0);
        printf("Hello message sent\n");

        if (!strncmp(buf, m_exitMsg, (size_t)(sizeof(m_exitMsg) - 1)))
           break;

        bzero(buf, m_maxLines);
    }
}
