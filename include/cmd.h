//
// Created by wery_a on 16/05/16.
//

#ifndef PSU_2015_MYIRC_CMD_H
# define PSU_2015_MYIRC_CMD_H

# include "server.h"
# include "cmd_list.h"

typedef enum COMMAND
{
    NICK, LIST, JOIN, PART, USERS, MSG, SEND_FILE, ACCEPT_FILE
}   COMMAND;

static const char *cmdlist_str[] =
{
        "/NICK", "/LIST", "/JOIN", "/PART", "/USERS", "/MSG",
        "/SEND_FILE", "/ACCEPT_FILE"
};

typedef bool    (*cmdlist_ptr)(Manager *, Client *, const char **);

static cmdlist_ptr cmdlist_func[] =
{
        &irc_nick, &irc_list, &irc_join, &irc_part, &irc_users,
        &irc_msg, &irc_send_file, &irc_accept_file
};

#endif //PSU_2015_MYIRC_CMD_H
