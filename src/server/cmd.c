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
#include <error.h>
#include <server.h>
#include "server.h"
#include "cmd_server.h"
#include "array.h"

bool    handle_cmds(Manager *manager, Client *client, const char *cmd_line)
{
    char    **array;

    if (cmd_line[0] == '\n')
        return (false);
    array = split(cmd_line, "\r\n");
    for (int i = 0; i < array_len((const char **)array); ++i)
    {
        DEBUG("cmd = %s\n", array[i]);
        handle_cmd(manager, client, array[i]);
    }
    return (true);
}

bool    handle_cmd(Manager *manager, Client *client, const char *cmd_line)
{
    char    **array;
    bool    ret;

    if (cmd_line[0] == '\n')
        return (false);
    array = split(cmd_line, " ");
    for (unsigned  int i = 0; i < sizeof(cmdlist_str) / sizeof(char *); ++i)
    {
        if (strcasecmp(array[0], cmdlist_str[i]))
            continue;
        ret = cmdlist_func[i](manager, client, (const char **)(&array[1]));
        free_array(array);
        return (ret);
    }
    free_array(array);
    return (true);
}

void    send_msg_to_all(Client *client, const char *msg, Channel *channel, bool himself)
{
    for (int i = 0; i < client->channel_size; ++i)
    {
        if (!channel || client->channels[i] == channel)
        {
            for (int j = 0; j < client->channels[i]->client_size; ++j)
            {
                if (client->channels[i]->clients[i] != client || himself)
                {
                    write_server_socket(channel->clients[i]->sock, msg);
                }
            }
        }
    }
}

bool        irc_nick(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    (void)manager;
    if (!arg || !arg[0] || replace((char *)arg[0], '\n', '\0')[0] == 0)
    {
        write_server_socket(client->sock, ERR_NONICKNAMEGIVEN);
        return (false);
    }
    if (getClient(manager, arg[0]))
    {
        write_server_socket(client->sock, ERR_NICKNAMEINUSE);
        return (false);
    }
    buffer = concat(3, client->username, " has changed nick to ", arg[0]);
    if (client->username)
        client->username = strdup(arg[0]);
    send_msg_to_all(client, buffer, NULL, true);
    free(buffer);
    return (true);
}

bool        irc_user(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    if (client->registered)
        return (write_server_socket(client->sock, ERR_ALREADYREGISTERED), false);
    buffer = concat(3, "001 ", WELCOME, client->username);
    write_server_socket(client->sock, buffer);
    free(buffer);
    client->registered = true;
    (void)manager;
    (void)arg;
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
    Channel *channel;

    if (!arg || !arg[0] || strlen(arg[0]) > 200
        || (arg[0][0] != '&' && arg[0][0] != '#'))
    {
        write_server_socket(client->sock, ERR_NOSUCHCHANNEL);
        return (false);
    }
    if (!(channel = getChannel(manager->channels, manager->channel_size, arg[0])))
        channel = new_channel(manager, arg[0]);
    join_channel(client, channel);
    buffer = concat(3, client->username, " has joined ", channel->name);
    send_msg_to_all(client, buffer, channel, true);
    free(buffer);
    return (true);
}

bool        irc_part(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;
    Channel *channel;

    if (!(channel = getChannel(manager->channels, manager->channel_size, arg[0])))
        write_server_socket(client->sock, ERR_NOTONCHANNEL);
    buffer = concat(3, client->username, " has left ", channel->name);
    send_msg_to_all(client, buffer, channel, true);
    free(buffer);
    part_channel(client, channel);
    return (true);
}

bool        irc_users(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;
    char    *tmp;

    (void)arg;
    buffer = NULL;
    for (int i = 0; i < manager->client_size; ++i)
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
    Channel *channel;
    Client  *client_dest;

    if (!arg[0])
        return (write_socket(client->sock, ERR_NORECIPIENT), false);
    if (!arg[1])
        return (write_socket(client->sock, ERR_NOTEXTTOSEND), false);
    buffer = concat(3, client->username, " : ", arg[1]);
    if (arg[0][0] == '#' || arg[0][0] == '&')
    {
        if (!(channel = getChannel(manager->channels, manager->channel_size, arg[0])))
            return (free(buffer), write_socket(client->sock, ERR_NOSUCHNICK), false);
        send_msg_to_all(client, buffer, channel, true);
    }
    else
    {
        if (!(client_dest = getClient(manager, arg[0])))
            return (free(buffer), write_socket(client->sock, ERR_NOSUCHNICK), false);
        write_server_socket(client_dest->sock, arg[1]);
    }
    free(buffer);
    return (true);
}

bool        irc_quit(Manager *manager, Client *client, const char **arg)
{
    write_socket(client->sock, "QUIT:");
    remove_client(manager, client->id);
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
