/*
** client.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 11:55:19 2016 Axel Vencatareddy
** Last update	Mon May 16 21:10:35 2016 Axel Vencatareddy
*/

#include "ptr.h"
#include <string.h>
#include <strings.h>

int		client(t_client *cl)
{
  char		buff[BUFSIZ];
  int		ret;
  int		i;

  if ((ret = read(0, &buff, BUFSIZ - 1)) == -1)
    return (my_error("read error", -1));
  buff[ret] = '\0';
  for (i = 0; tab[i]; i++)
    {
      if (!strncasecmp(buff, tab[i], strlen(tab[i])))
        {
          cl->cmd = buff;
          return (ptr[i](cl));
        }
    }
  if (cl->fd_nb == 2)
    {
      if (write(cl->fds[1].fd, buff, strlen(buff)) == -1)
        {
          perror("write error");
          return (-1);
        }
    }
  else
    printf("530 Please log in to a server first.");
  return (0);
}

void		init_struct(t_client *cl)
{
  cl->fds[0].fd = 0;
  cl->fds[1].fd = -1;
  cl->fd_nb = 1;
  cl->fds[0].events = POLLIN;
  cl->fds[1].events = POLLIN;
  cl->fds[1].revents = POLLNVAL;
  cl->is_end = false;
  cl->cmd = NULL;
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
              if (client(&cl) == -1)
                return (-1);
            }
          if (cl.fd_nb == 2 && cl.fds[1].revents & POLLIN)
            {
              if ((fd = read(cl.fds[1].fd, &buff, BUFSIZ - 1)) == -1)
                return (my_error("read error", -1));
              buff[fd] = '\0';
              printf("%s\n", buff);
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
