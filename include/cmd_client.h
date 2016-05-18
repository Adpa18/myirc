/*
** ptr.h for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 18:39:05 2016 Axel Vencatareddy
** Last update	Mon May 16 21:05:27 2016 Axel Vencatareddy
*/

#ifndef CMD_CLIENT_H_
# define CMD_CLIENT_H_

# include "cmd_list_client.h"

typedef enum COMMAND
{
    SERVER = 0, NICK, USER, LIST, JOIN, PART, USERS, SEND_FILE,
    ACCEPT_FILE, HELP, QUIT, NO_CMD
}   COMMAND;

static const char *cmdlist_str[] =
{
  "/SERVER", "/NICK", "/USER", "/LIST", "/JOIN", "/PART", "/USERS",
  "/SEND_FILE", "/ACCEPT_FILE", "/HELP", "/QUIT"
};

typedef bool	(*cmdlist_ptr)(t_client *, const char **);

static cmdlist_ptr cmdlist_func[] =
{
  &irc_server, &irc_nick, &irc_user, &irc_list, &irc_join, &irc_part,
  &irc_users, &irc_send_file, &irc_accept_file, &irc_help, &irc_quit
};

#endif /* !CMD_CLIENT_H_ */
