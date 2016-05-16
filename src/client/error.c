/*
** error.c for my_ftp in /home/vencat_a/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Axel Vencatareddy
** Login   <vencat_a@epitech.net>
** 
** Started on  Sat May 14 14:08:24 2016 Axel Vencatareddy
** Last update Sat May 14 14:08:25 2016 Axel Vencatareddy
*/

#include <stdio.h>

int	my_error(char *msg, int ret)
{
  perror(msg);
  return (ret);
}
