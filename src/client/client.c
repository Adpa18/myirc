/*
** client.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 11:55:19 2016 Axel Vencatareddy
** Last update	Mon May 16 21:10:35 2016 Axel Vencatareddy
*/

#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "client.h"

bool    killed = false;

void        kill_sig(int sig)
{
    if (sig == SIGINT)
    {
        write(1, KILL_SIGINT, strlen(KILL_SIGINT));
        killed = true;
    }
}

bool    init_select(fd_set *rdfs, t_client *cl)
{
    FD_ZERO(rdfs);
    FD_SET(STDIN_FILENO, rdfs);
    if (cl->isConnected)
        FD_SET(cl->sock, rdfs);
    if (select(cl->max_fd + 1, rdfs, NULL, NULL, NULL) == -1)
    {
        perror("select");
        close(cl->sock);
        return (false);
    }
    return (true);
}

void    listen_client(t_client *cl)
{
    char    *buffer;

    if (!(buffer = read_socket(cl->sock)))
    {
        write_socket(STDOUT_FILENO, EOT_SERVER);
        cl->isConnected = false;
    }
    else
    {
        write_socket(STDOUT_FILENO, buffer);
        write(STDOUT_FILENO, "\n", 1);
        free(buffer);
    }
}

int		main()
{
    signal(SIGINT, &kill_sig);
    t_client  cl;
    fd_set    rdfs;

    cl.max_fd = STDIN_FILENO;
    cl.isConnected = false;
    while (!killed)
    {
        if (!init_select(&rdfs, &cl))
            break;
        if (FD_ISSET(STDIN_FILENO, &rdfs))
            handle_cmd(&cl);
        else if (FD_ISSET(cl.sock, &rdfs))
            listen_client(&cl);
    }
    return (0);
}