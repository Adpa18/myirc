//
// Created by wery_a on 15/05/16.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <server.h>
#include "server.h"

char    *genNick()
{
    char    buffer[BUFF_SIZE];
    sprintf(buffer, "%d", rand() % 100000 + 10000);
    return (concat(NICK_PREFIX, buffer, 0));
}

bool    new_client(SOCKET sock, fd_set *rdfs, Manager *manager)
{
    SOCKET      csock;
    SOCKADDR_IN csin;
    socklen_t   sinsize;

    sinsize = sizeof(csin);
    if ((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) == -1)
    {
        return (perror("accept"), false);
    }
    if (manager->size >= MAX_CLIENTS)
    {
        write_socket(csock, ERROR_MAX);
        return (close(csock), false);
    }
    FD_SET(csock, rdfs);
    manager->max_fd = csock > manager->max_fd ? csock : manager->max_fd;
    manager->clients[manager->size].sock = csock;
    manager->clients[manager->size].username = genNick();
    ++manager->size;
    write_socket(csock, WELCOME);
    return (true);
}

void    remove_client(Manager *manager, int to_remove)
{
    close(manager->clients[to_remove].sock);
    memmove(manager->clients + to_remove, manager->clients + to_remove + 1,
            (manager->size - to_remove - 1) * sizeof(Client));
    --manager->size;
}

void    listen_clients(fd_set *rdfs, Manager *manager)
{
    char    *buffer;

    for (int i = 0; i < manager->size; i++)
    {
        if (!FD_ISSET(manager->clients[i].sock, rdfs))
            continue;
        if ((buffer = read_socket(manager->clients[i].sock)) == NULL)
        {
            buffer = concat(manager->clients[i].username, " is disconnected !", 0);
            remove_client(manager, i);
            printf(EOT_CLIENT, i);
        }
        handle_cmd(manager, &manager->clients[i], buffer);
        free(buffer);
        break;
    }
}
