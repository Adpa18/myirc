/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:11:49 2016 Adrien WERY
*/

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
    return (concat(2, NICK_PREFIX, buffer));
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
    if (manager->client_size >= MAX_CLIENTS)
    {
        write_socket(csock, ERROR_MAX);
        return (close(csock), false);
    }
    FD_SET(csock, rdfs);
    manager->max_fd = csock > manager->max_fd ? csock : manager->max_fd;
    manager->clients[manager->client_size].sock = csock;
    manager->clients[manager->client_size].username = genNick();
    manager->clients[manager->client_size].channel_size = 0;
    manager->clients[manager->client_size].id = manager->client_size;
    ++manager->client_size;
    DEBUG("New Client %s\n", manager->clients[manager->client_size - 1].username);
    return (true);
}

void    remove_client(Manager *manager, int to_remove)
{
    free(manager->clients[to_remove].username);
    close(manager->clients[to_remove].sock);
    memmove(manager->clients + to_remove, manager->clients + to_remove + 1,
            (manager->client_size - to_remove - 1) * sizeof(Client));
    --manager->client_size;
}

void    listen_clients(fd_set *rdfs, Manager *manager)
{
    char    *buffer;

    for (int i = 0; i < manager->client_size; i++)
    {
        if (!FD_ISSET(manager->clients[i].sock, rdfs))
            continue;
        if ((buffer = read_socket(manager->clients[i].sock)) == NULL)
        {
            buffer = concat(2, manager->clients[i].username, " is disconnected !");
            send_msg_to_all(&manager->clients[i], buffer, NULL, false);
            remove_client(manager, i);
            DEBUG("%s\n", buffer);
        }
        else
            handle_cmds(manager, &manager->clients[i], buffer);
        free(buffer);
        break;
    }
}
