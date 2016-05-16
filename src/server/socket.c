//
// Created by wery_a on 15/05/16.
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

extern bool    killed;

bool    write_socket(SOCKET sock, const char *buffer)
{
    if (!buffer)
        return (false);
    write(sock, buffer, strlen(buffer));
    return (true);
}

char    *read_socket(SOCKET sock)
{
    char    buffer[BUFF_SIZE];
    int     n;

    if ((n = read(sock, buffer, BUFF_SIZE - 1)) == -1)
    {
        perror("read");
        return (NULL);
    }
    buffer[n] = 0;
    return (strdup(buffer));
}

SOCKET      init_listen(SOCKET sock)
{
    if (listen(sock, MAX_CLIENTS) == -1)
    {
        perror("listen");
        close(sock);
        return (-1);
    }
    return (sock);
}

SOCKET      init_server(unsigned int port)
{
    SOCKET      sock;
    SOCKADDR_IN s_in;
    int         enable;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return (-1);
    }
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = INADDR_ANY;
    enable = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
        perror("setsockopt");
    if (bind(sock, (SOCKADDR *)&s_in, sizeof(s_in)) == -1)
    {
        perror("bind");
        close(sock);
        return (-1);
    }
    return (init_listen(sock));
}