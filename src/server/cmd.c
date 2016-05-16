//
// Created by wery_a on 16/05/16.
//

#include <server.h>
#include <string.h>
#include <cmd.h>
#include <stdlib.h>
#include "array.h"

bool    handle_cmd(Manager *manager, Client *client, const char *cmd_line)
{
    char    **array;
    bool    ret;

    array = split(cmd_line, " ");
    for (unsigned  int i = 0; i < sizeof(cmdlist_str) / sizeof(char *); ++i)
    {
        if (strcasecmp(array[1], cmdlist_str[i]) == 0)
        {
            ret = cmdlist_func[i](manager, client, (const char **)(&array[1]));
            free_array(array);
            return (ret);
        }
    }
    send_msg_to_all(manager, client, cmd_line);
    free_array(array);
    return (true);
}

void    send_msg_to_all(Manager *manager, Client *client, const char *msg)
{
    for (int i = 0; i < manager->size; i++)
    {
        if (!strcmp(client->channel, manager->clients[i].channel)
                && manager->clients[i].sock != client->sock)
        {
            write_socket(manager->clients[i].sock, msg);
        }
    }
}

bool        irc_nick(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    if (!arg || !arg[0])
    {
        write_socket(client->sock, "Invalid Username\n");
        return (false);
    }
    // if same as someone erase both
    buffer = concat(client->username, " has changed nick to ", arg[0]);
    if (client->username)
        client->username = strdup(arg[0]);
    send_msg_to_all(manager, client, buffer);
    free(buffer);
    return (true);
}

bool        irc_list(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    (void)client;
    (void)arg;
    return (true);
}

bool        irc_join(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    if (!arg || !arg[0] || strlen(arg[0]) > 200
        || (arg[0][0] != '&' && arg[0][0] != '#'))
    {
        write_socket(client->sock, "Invalid Channel\n");
        return (false);
    }
    buffer = concat(arg[0], " has joined ", client->channel);
    send_msg_to_all(manager, client, buffer);
    free(buffer);
    strcpy(client->channel, arg[0]);
    return (true);
}

bool        irc_part(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    (void)arg;
    memset(client->channel, 0, 200);
    return (true);
}

bool        irc_users(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    (void)client;
    (void)arg;
    return (true);
}

bool        irc_send_file(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    (void)client;
    (void)arg;
    return (true);
}

bool        irc_accept_file(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    (void)client;
    (void)arg;
    return (true);
}