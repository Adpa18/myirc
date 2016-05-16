/*
** get_next_line.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src
**
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
**
** Started on  Sat May 14 14:08:40 2016 Axel Vencatareddy
** Last update	Sat May 14 20:07:13 2016 Axel Vencatareddy
*/

#include "get_next_line.h"

char	*my_line(char buff[BUFSIZ + 1], char *line, int *start, int pos)
{
  int	len;
  char	*new_line;
  int	i;
  int	j;

  i = 0;
  j = 0;
  len = my_strlen(line);
  if ((new_line = malloc((len + pos + 1) * sizeof(char) + 1)) == NULL)
    return (NULL);
  while (i < len)
    {
      new_line[i] = line[i];
      ++i;
    }
  while (j < pos)
    {
      new_line[i + j] = buff[*start + j];
      ++j;
    }
  new_line[i + j] = '\0';
  *start = *start + pos;
  if (line != NULL)
    free(line);
  return (new_line);
}

void		init_gnl_struct(t_gnl *get_nl, char indic, int fd)
{
  if (indic == 1)
    {
      get_nl->line = NULL;
      get_nl->pos = 0;
      get_nl->ctrl_d = 0;
      get_nl->fd = fd;
      get_nl->error = FALSE;
    }
  if (indic == 2)
    {
      get_nl->ctrl_d = 1;
      get_nl->pos++;
    }
}

char		*my_gnl_error(int mode)
{
  if (mode == FALSE || mode == 1)
    return (NULL);
  else
    return (strdup("^C"));
}

int		get_next_line_norm(t_gnl *get_nl, int *start,
				   int *size, char (*buff)[BUFSIZ + 1])
{
  *start = 0;
  get_nl->pos = 0;
  if (((*size) = read(get_nl->fd, *buff, BUFSIZ)) < 0)
    return (my_error("read() error", FALSE));
  else if (*size == 0 && get_nl->ctrl_d == 0)
    {
      get_nl->error = 1;
      return (1);
    }
  else if (*size == -1)
    {
      get_nl->error = 2;
      return (2);
    }
  (*buff)[*size] = 0;
  return (TRUE);
}

char		*get_next_line(const int fd)
{
  t_gnl		get_nl;
  static int    start = 0;
  static int    size = 0;
  static char	buff[BUFSIZ + 1];

  get_nl.i = 0;
  init_gnl_struct(&get_nl, 1, fd);
  if (start == 0)
    while (get_nl.i < BUFSIZ)
      buff[get_nl.i++] = 0;
  while (42)
    {
      if (start >= size)
	if (get_next_line_norm(&get_nl, &start, &size, &buff) != TRUE)
	  return (my_gnl_error(get_nl.error));
      if (buff[start + get_nl.pos] == '\n' && start + get_nl.pos > 0
          && buff[start + get_nl.pos - 1] == '\r')
	return (my_line(buff, get_nl.line, &(start), get_nl.pos + 1));
      if (start + get_nl.pos >= size)
	get_nl.line = my_line(buff, get_nl.line, &(start), get_nl.pos + 1);
      init_gnl_struct(&get_nl, 2, fd);
    }
}
