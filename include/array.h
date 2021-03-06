/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef ARRAY_H
# define ARRAY_H

int     array_len(const char **array);
void    free_array(char **array);
char    **split(const char *s, const char *delim);
char    *merge(const char **array, const char *delim);

#endif /* !ARRAY_H */
