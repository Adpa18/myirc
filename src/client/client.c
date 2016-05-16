/*
** client.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 11:55:19 2016 Axel Vencatareddy
** Last update	Mon May 16 16:55:51 2016 Axel Vencatareddy
*/

#include "client.h"

int		client()
{
  char		buff[BUFSIZ];
  int		ret;

  if ((ret = read(0, &buff, BUFSIZ - 1)) == -1)
    return (my_error("read error", -1));
  buff[ret] = '\0';
  printf("This, was written on stdin : \"%s\"\n", buff);
  return (0);
}

void		init_struct(t_client *cl)
{
  cl->fds[0].fd = 0;
  cl->fds[1].fd = -1;
  cl->fd_nb = 1;
  cl->fds[0].events = POLLIN;
  cl->fds[1].events = POLLIN;
  cl->is_end = false;
}

int		my_poll()
{
  int		fd;
  t_client	cl;
  char		buff[BUFSIZ];

  init_struct(&cl);
  while (cl.is_end == false)
    {
      fd = poll(cl.fds, cl.fd_nb, cl.timeout);
      if (fd > 0)
        {
          if (cl.fds[0].revents & POLLIN)
            {
              if (client() == -1)
                return (-1);
            }
          if (cl.fd_nb == 2 && cl.fds[1].revents & POLLIN)
            {
              if ((fd = read(cl.fds[1].fd, &buff, BUFSIZ - 1)) == -1)
                return (my_error("read error", -1));
              buff[fd] = '\0';
              write(1, buff, fd);
            }
        }
    }
  return (0);
}

int		main()
{
  if (my_poll() == -1)
    return (-1);
  return (0);
}
