//
// Created by wery_a on 16/05/16.
//

#ifndef PSU_2015_MYIRC_CMD_LIST_H
# define PSU_2015_MYIRC_CMD_LIST_H

# include "server.h"

bool    irc_nick(Manager *manager, Client *client, const char **arg);
bool    irc_list(Manager *manager, Client *client, const char **arg);
bool    irc_join(Manager *manager, Client *client, const char **arg);
bool    irc_part(Manager *manager, Client *client, const char **arg);
bool    irc_users(Manager *manager, Client *client, const char **arg);
bool    irc_send_file(Manager *manager, Client *client, const char **arg);
bool    irc_accept_file(Manager *manager, Client *client, const char **arg);

#endif //PSU_2015_MYIRC_CMD_LIST_H
