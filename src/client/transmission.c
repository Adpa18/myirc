/*
** transmission.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 14:13:31 2016 Axel Vencatareddy
** Last update	Mon May 16 14:14:35 2016 Axel Vencatareddy
*/

#include "transmission.h"

int		send_msg_client(int fd, char *msg)
{
  if (write(fd, msg, strlen(msg)) == -1)
    {
      perror("write() error");
      return (-1);
    }
  if (write(fd, "\r\n", 2) == -1)
    {
      perror("write() error");
      return (-1);
    }
  return (0);
}

int		send_msg(int fd, char *msg)
{
  if (write(fd, msg, strlen(msg)) == -1)
    {
      perror("write() error");
      return (-1);
    }
  return (0);
}

int		accept_socket(int sock_fd)
{
  t_sock_in	s_in;
  socklen_t	size;
  int		client_fd;

  size = sizeof(s_in);
  if ((client_fd = accept(sock_fd, (struct sockaddr *)&s_in, &size)) == -1)
    {
      perror("accept() error");
      return (-1);
    }
  return (client_fd);
}

char		*recv_cmd(int fd_sock)
{
  char		*buf;

  if ((buf = get_next_line(fd_sock)) == NULL)
    return (NULL);
  return (buf);
}
