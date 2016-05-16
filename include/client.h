/*
** client.h for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 11:57:40 2016 Axel Vencatareddy
** Last update	Mon May 16 16:54:53 2016 Axel Vencatareddy
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

int	open_socket();
int	close_socket(int fd_sock);
int	connect_socket(int fd_sock, int port, char *ip);
char	*recv_cmd(int fd_sock);
int	my_error(char *, int);

typedef enum { false, true } bool;

typedef struct	s_client
{
  char		*cmd;
  struct pollfd	fds[2];
  int		fd_nb;
  int		timeout;
  bool		is_end;
}		t_client;

#endif /* !CLIENT_H_ */
