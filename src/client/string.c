/*
** string.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 14:13:23 2016 Axel Vencatareddy
** Last update	Mon May 16 14:14:13 2016 Axel Vencatareddy
*/

#include "my_string.h"

void	my_free_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i])
    {
      if (tab[i])
        free(tab[i]);
      i++;
    }
  if (tab)
    free(tab);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}

int	my_malloc(char *str)
{
  int	i;
  int	count;

  i = 0;
  count	= 0;
  while (str && str[i])
    {
      if (str[i] == ' ' || str[i] == '\t')
	{
	  while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	    i++;
	  count++;
	}
      if (!str[i])
	return (count);
      i++;
    }
  return (count);
}

char	**init(char *str, int *i, int *j)
{
  char	**tab;
  int	words;

  *i = 0;
  *j = 0;
  words = my_malloc(str) + 1;
  if ((tab = malloc(sizeof(char*) * (words + 1))) == NULL)
    return (NULL);
  return (tab);
}

char	**my_str_to_wordtab(char *str)
{
  char	**tab;
  int	i;
  int	j;
  int	c;

  tab = init(str, &i, &j);
  while (str[i])
    {
      if ((tab[j] = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
	return (NULL);
      while (str[i] && (str[i] == ' ' || str[i] == '\t'))
	i++;
      c = 0;
      while (str[i] && str[i] != ' ' && str[i] != '\t')
	tab[j][c++] = str[i++];
      tab[j][c] = '\0';
      c--;
      while (c >= 0 && (tab[j][c] == '\n' || tab[j][c] == '\r'))
        tab[j][c--] = '\0';
      while (str[i] == ' ' || str[i] == '\t')
	i++;
      j++;
    }
  tab[j] = NULL;
  return (tab);
}
