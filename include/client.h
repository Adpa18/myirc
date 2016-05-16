/*
** client.h for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 11:57:40 2016 Axel Vencatareddy
** Last update	Mon May 16 21:07:57 2016 Axel Vencatareddy
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

typedef enum { false, true } bool;

typedef struct	s_client
{
  char		*cmd;
  struct pollfd	fds[2];
  int		fd_nb;
  int		timeout;
  bool		is_end;
}		t_client;

int	open_socket();
int	close_socket(int fd_sock);
int	connect_socket(int fd_sock, int port, char *ip);
char	*recv_cmd(int fd_sock);
int	my_error(char *, int);
int	my_server(t_client *);
int	my_send_file(t_client *);
int	my_accept_file(t_client *);
int	my_help(t_client *);
int	my_exit(t_client *);
int	my_free(void *, int);

#endif /* !CLIENT_H_ */
