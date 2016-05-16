/*
** connect.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 13:31:35 2016 Axel Vencatareddy
** Last update	Mon May 16 16:54:40 2016 Axel Vencatareddy
*/

#include "client.h"
#include <string.h>

int	my_server(t_client *cl)
{
  char	*ip;
  int	port;

  ip = strtok(cl->cmd, ":");
  port = atoi(strtok(NULL, ":"));
  port = port < 0 ? 194 : port;
  if (cl->fds[1].fd == -1)
    if (close_socket(cl->fds[1].fd) == -1)
      return (-1);
  if ((cl->fds[1].fd = open_socket()) == -1)
    return (-1);
  if (connect_socket(cl->fds[1].fd, port, ip) == -1)
    return (-1);
  cl->fd_nb = 2;
  return (0);
}
