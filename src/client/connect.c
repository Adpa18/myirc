/*
** connect.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 13:31:35 2016 Axel Vencatareddy
** Last update	Mon May 16 21:13:01 2016 Axel Vencatareddy
*/

#include "client.h"
#include <string.h>

int	my_exit(t_client *cl)
{
  cl->is_end = true;
  return (0);
}

int	my_server(t_client *cl)
{
  char	*ip;
  int	port;

  ip = strtok(cl->cmd, " ");
  ip = strtok(NULL, ":");
  port = atoi(strtok(NULL, ":"));
  port = port < 0 ? 194 : port;
  if (cl->fds[1].fd != -1)
    if (close_socket(cl->fds[1].fd) == -1)
        return (-1);
  if ((cl->fds[1].fd = open_socket()) == -1)
    return (-1);
  if (connect_socket(cl->fds[1].fd, port, ip) == -1)
    return (-1);
  cl->fd_nb = 2;
  return (0);
}

int	my_help(t_client *cl)
{
  printf("The following functions are available :\n\n - /server _host_[:_port_]\
 : Connect to a server.\n\n - /nick _nickname_ : define the nickname of the use\
r on the channel.\n\n - /list [string] : list the available channels. Only disp\
lays those whose names\n\t\t    match with the [string] if specified.\n\n - /jo\
in _channel_ : join a channel.\n\n - /part _channel_ : quit the channel.\n\n - \
/users : list all the users connected to the channel.\n\n - _message_ : send a \
message to the users connected to the channel.\n\n - /msg _nickname_ _message_ \
: send a msg to a specific user.\n\n - /send_file _nickname_ _file_ : send a fi\
le to an user.\n\n - /accept_file _nickname_ : accept a file from another user \
of the channel.\n\n");
  cl->cmd[0] = 0;
  return (0);
}

int	my_send_file(t_client *cl)
{
  (void)cl;
  return (0);
}

int	my_accept_file(t_client *cl)
{
  (void)cl;
  return (0);
}
