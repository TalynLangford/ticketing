#include "Server.h"

Server::Server() : m_port(5432), m_backlog(10), m_maxLines(1024) {}
Server::Server(int m_port, int m_backlog, int m_maxLines) : m_port(m_port), m_backlog(m_backlog), m_maxLines(m_maxLines) {}
Server::~Server() {}

bool Server::startServer(IService &service)
{
    ServerDeps deps = configureServer();
    bindServer(deps);
    listenServer(deps, service);
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

    /*
        Fails on mac, works on Ubuntu
        
        Either come up with a workaround or set options based on os
    */
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

void Server::handleConnection(int fd, int addrlen, int m_maxLines, IService &service)
{
    int valread;
    char buf[1024] = {0};
    char const *msg = "Hello from the server";
    std::cout << "accepted..." << fd << std::endl;

    // truncates long messages. Use recv in while to capture.
    valread = read(fd, buf, m_maxLines);

    std::cout << "read : " << valread << std::endl;
    if (valread < 0)
    {
        perror("valread");
    }

    // should this be in helper method?
    std::string temp = service.functionHandle(""); // empty string (for now!)
    const char* resp = temp.c_str();

    printf("%s\n",buf);
    send(fd, resp, strlen(resp), 0);
    printf("Hello message sent\n");

    bzero(buf, m_maxLines);
}

void Server::listenServer(Server::ServerDeps deps, IService &service)
{
    int new_s;
    int addrlen = sizeof(deps.address);
    

    if (listen(deps.fd, m_backlog) < 0)
    {
        perror("listen");
        exit(1);
    }

    std::cout << "listening..." << std::endl;

    while(true)
    {
        if ((new_s = accept(deps.fd, (struct sockaddr*)&deps.address, (socklen_t*)&addrlen)) < 0)
        {
            perror("accept");
            exit(1);
        }

        async(handleConnection, new_s, addrlen, m_maxLines, std::ref(service));
    }
}
