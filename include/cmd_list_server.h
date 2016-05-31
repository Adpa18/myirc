/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef PSU_2015_MYIRC_CMD_LIST_H
# define PSU_2015_MYIRC_CMD_LIST_H

# include "server.h"

bool    irc_nick(Manager *manager, Client *client, const char **arg);
bool    irc_user(Manager *manager, Client *client, const char **arg);
bool    irc_list(Manager *manager, Client *client, const char **arg);
bool    irc_join(Manager *manager, Client *client, const char **arg);
bool    irc_part(Manager *manager, Client *client, const char **arg);
bool    irc_users(Manager *manager, Client *client, const char **arg);
bool    irc_names(Manager *manager, Client *client, const char **arg);
bool    irc_msg(Manager *manager, Client *client, const char **arg);
bool    irc_quit(Manager *manager, Client *client, const char **arg);
bool    irc_send_file(Manager *manager, Client *client, const char **arg);
bool    irc_accept_file(Manager *manager, Client *client, const char **arg);

#endif //PSU_2015_MYIRC_CMD_LIST_H
