/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef PSU_2015_MYIRC_CMD_H
# define PSU_2015_MYIRC_CMD_H

# include "server.h"
# include "cmd_list_server.h"

typedef enum COMMAND
{
  NICK, USER, LIST, JOIN, PART, USERS, NAMES, PRIVMSG, QUIT,
    SEND_FILE, ACCEPT_FILE
}   COMMAND;

static const char *cmdlist_str[] =
{
  "NICK", "USER", "LIST", "JOIN", "PART", "USERS", "NAMES", "PRIVMSG", "QUIT",
  "SEND_FILE", "ACCEPT_FILE"
};

typedef bool	(*cmdlist_ptr)(Manager *, Client *, const char **);

static cmdlist_ptr cmdlist_func[] =
{
  &irc_nick, &irc_user, &irc_list, &irc_join, &irc_part, &irc_users,
  &irc_names, &irc_msg, &irc_quit, &irc_send_file, &irc_accept_file
};

#endif //PSU_2015_MYIRC_CMD_H
