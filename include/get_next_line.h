/*
** get_next_line.h for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/include
**
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
**
** Started on  Sat May 14 14:15:50 2016 Axel Vencatareddy
** Last update	Mon May 16 16:41:34 2016 Axel Vencatareddy
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define BUFSIZ 1024
# define FALSE (-1)
# define TRUE (0)
# define UNUSED __attribute__((unused))

typedef struct	s_gnl
{
  int		pos;
  char		*line;
  char		ctrl_d;
  int		i;
  int		error;
  int		fd;
}		t_gnl;

int	my_strlen(char *);
int	my_error(char *, int);

#endif /* !GET_NEXT_LINE_H_ */
