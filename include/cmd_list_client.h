/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef PSU_2015_MYIRC_CMD_LIST_CLIENT_H
# define PSU_2015_MYIRC_CMD_LIST_CLIENT_H

# include "client.h"
# include "common.h"

# define INVALID_ARG    "Invalid Arguments\n"

void    send_cmd(SOCKET sock, const char *cmd, const char *arg);
bool    irc_server(t_client *cl, const char **arg);
bool    irc_nick(t_client *cl, const char **arg);
bool    irc_user(t_client *cl, const char **arg);
bool    irc_list(t_client *cl, const char **arg);
bool    irc_join(t_client *cl, const char **arg);
bool    irc_part(t_client *cl, const char **arg);
bool    irc_users(t_client *cl, const char **arg);
bool    irc_names(t_client *cl, const char **arg);
bool    irc_msg(t_client *cl, const char **arg);
bool    irc_send_file(t_client *cl, const char **arg);
bool    irc_accept_file(t_client *cl, const char **arg);
bool    irc_help(t_client *cl, const char **arg);
bool    irc_quit(t_client *cl, const char **arg);

#endif //PSU_2015_MYIRC_CMD_LIST_CLIENT_H
