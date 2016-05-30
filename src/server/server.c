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
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <server.h>
#include "server.h"

bool    killed = false;

void        kill_sig(int sig)
{
    if (sig == SIGINT)
    {
        write(1, KILL_SIGINT, strlen(KILL_SIGINT));
        killed = true;
    }
}

void    clean_manager(Manager *manager)
{
    for (int i = 0; i < manager->client_size; i++)
    {
        close(manager->clients[i].sock);
    }
}

bool    init_select(fd_set *rdfs, int sock, Manager *manager)
{
    FD_ZERO(rdfs);
    FD_SET(sock, rdfs);
    for (int i = 0; i < manager->client_size; ++i)
    {
        FD_SET(manager->clients[i].sock, rdfs);
    }
    if (select(manager->max_fd + 1, rdfs, NULL, NULL, NULL) == -1)
    {
        perror("select");
        close(sock);
        return (false);
    }
    return (true);
}

void    server(unsigned int port)
{
    Manager manager;
    SOCKET  sock;
    fd_set  rdfs;

    if ((sock = init_server(port)) == -1)
        return;
    manager.client_size = 0;
    manager.channel_size = 0;
    manager.max_fd = sock;
    while (!killed)
    {
        if (!init_select(&rdfs, sock, &manager))
            break;
        if (FD_ISSET(sock, &rdfs))
            new_client(sock, &rdfs, &manager);
        else
            listen_clients(&rdfs, &manager);
    }
    clean_manager(&manager);
    close(sock);
}

int main(int ac, char **av)
{
    unsigned int    port;

    srand(time(NULL));
    if (ac < 2 || !(port = atoi(av[1])))
    {
        write(1, USAGE, strlen(USAGE));
        return (1);
    }
    signal(SIGINT, &kill_sig);
    server(port);
    return (0);
}
