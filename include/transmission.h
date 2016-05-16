/*
** transmission.h for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/include
**
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
**
** Started on  Sat May 14 14:17:26 2016 Axel Vencatareddy
** Last update	Mon May 16 16:16:33 2016 Axel Vencatareddy
*/

#ifndef TRANSMISSION_H_
# define TRANSMISSION_H_

# include "socket_client.h"
# include <string.h>

char	*get_next_line(const int fd);

#endif /* !TRANSMISSION_H_ */
