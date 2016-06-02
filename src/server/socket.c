/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

extern bool    killed;

bool    write_client_socket(SOCKET sock, Client *client, const char *code,
                            const char *msg)
{
    char    *tmp;
    char    *name;
    bool    ret;

    name = (client->reg) ? client->reg : concat(2, client->username, "@*");
    tmp = concat(9, ":", client->username, "!~", name, " ",
                 code, " :", msg, CRLF);
    ret = write_socket(sock, tmp);
    free(tmp);
    if (!client->reg)
        free (name);
    return (ret);
}

bool    write_server_socket(Client *client, const char *code,
                            const char *msg)
{
    char    *tmp;
    bool    ret;

    tmp = concat(6, ":"SERVER_NAME" ", code, " ", client->username,
                 msg, CRLF);
    ret = write_socket(client->sock, tmp);
    free(tmp);
    return (ret);
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
