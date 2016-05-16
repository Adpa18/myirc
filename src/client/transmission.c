/*
** transmission.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 14:13:31 2016 Axel Vencatareddy
** Last update	Mon May 16 21:17:33 2016 Axel Vencatareddy
*/

#include "transmission.h"

int		send_msg(int fd, char *msg)
{
  if (write(fd, msg, strlen(msg)) == -1)
    {
      perror("write() error");
      return (-1);
    }
  return (0);
}
