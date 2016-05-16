/*
** socket.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 13:20:22 2016 Axel Vencatareddy
** Last update	Mon May 16 21:16:41 2016 Axel Vencatareddy
*/

#include "socket_client.h"

int		open_socket()
{
  t_protoent	*pe;
  int		fd_sock;

  if ((pe = getprotobyname("TCP")) == NULL)
    {
      perror("getprotobyname() error");
      return (-1);
    }
  if ((fd_sock = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      perror("socket() error");
      return (-1);
    }
  return (fd_sock);
}

int		close_socket(int fd_sock)
{
  if (close(fd_sock) == -1)
    {
      perror("close() error");
      return (-1);
    }
  return (0);
}

int		connect_socket(int fd_sock, int port, char *ip)
{
  t_sock_in	s_in;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  if (!inet_aton(ip, &(s_in.sin_addr)))
    {
      fprintf(stderr, "IP address error\n");
      if (close(fd_sock) == -1)
        perror("close() error");
      return (-1);
    }
  if (connect(fd_sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      perror("connect() error");
      if (close(fd_sock) == -1)
        perror("close() error");
      return (-1);
    }
  return (0);
}
