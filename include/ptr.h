/*
** ptr.h for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 18:39:05 2016 Axel Vencatareddy
** Last update	Mon May 16 21:05:27 2016 Axel Vencatareddy
*/

#ifndef PTR_H_
# define PTR_H_

#include "client.h"

static const char	*tab[] = {
  "/SERVER", "/ACCEPT_FILE", "/SEND_FILE", "/HELP", "/EXIT"
};

static int (*ptr[])(t_client *) =
{
  &my_server, &my_send_file, &my_accept_file, &my_help, &my_exit
};

#endif /* !PTR_H_ */
