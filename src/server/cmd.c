/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:11:09 2016 Adrien WERY
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "cmd_server.h"
#include "array.h"

bool    handle_cmd(Manager *manager, Client *client, const char *cmd_line)
{
    char    **array;
    char    *buffer;
    bool    ret;

    if (cmd_line[0] == '\n')
        return (false);
    array = split(cmd_line, " ");
    for (unsigned  int i = 0; i < sizeof(cmdlist_str) / sizeof(char *); ++i)
    {
        if (strcasecmp(array[0], cmdlist_str[i]) == 0)
        {
            ret = cmdlist_func[i](manager, client, (const char **)(&array[1]));
            free_array(array);
            return (ret);
        }
    }
    buffer = concat(3, client->username, " : ", cmd_line);
    send_msg_to_all(manager, client, buffer, false);
    free_array(array);
    free(buffer);
    return (true);
}

void    send_msg_to_all(Manager *manager, Client *client, const char *msg, bool himself)
{
    for (int i = 0; i < manager->size; i++)
    {
        if (!strcmp(client->channel, manager->clients[i].channel)
                && (manager->clients[i].sock != client->sock || himself))
        {
            write_socket(manager->clients[i].sock, msg);
        }
    }
}

bool        irc_nick(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    if (!arg || !arg[0] || replace((char *)arg[0], '\n', '\0')[0] == 0)
    {
        write_socket(client->sock, "Invalid Username\n");
        return (false);
    }
    // if same as someone erase both
    buffer = concat(3, client->username, " has changed nick to ", arg[0]);
    if (client->username)
        client->username = strdup(arg[0]);
    send_msg_to_all(manager, client, buffer, true);
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
    strcpy(client->channel, arg[0]);
    buffer = concat(3, client->username, " has joined ", client->channel);
    send_msg_to_all(manager, client, buffer, true);
    free(buffer);
    return (true);
}

bool        irc_part(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    (void)manager;
    (void)arg;
    buffer = concat(3, client->username, " has left ", client->channel);
    send_msg_to_all(manager, client, buffer, true);
    free(buffer);
    memset(client->channel, 0, 200);
    return (true);
}

bool        irc_users(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;
    char    *tmp;

    (void)arg;
    buffer = NULL;
    for (int i = 0; i < manager->size; ++i)
    {
        tmp = buffer;
        buffer = concat(3, buffer, manager->clients[i].username, "\n");
        free(tmp);
    }
    write_socket(client->sock, buffer);
    free(buffer);
    return (true);
}

bool        irc_msg(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    if (!arg[0] || !arg[1])
    {
        write_socket(client->sock, "Invalid Nick or Message\n");
        return (false);
    }
    for (int i = 0; i < manager->size; ++i)
    {
        if (!strcmp(arg[0], manager->clients[i].username))
        {
            buffer = concat(3, client->username, " : ", arg[1]);
            write_socket(manager->clients[i].sock, buffer);
            free(buffer);
            break;
        }
    }
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
