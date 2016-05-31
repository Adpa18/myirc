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

void    send_msg_to_all(Client *client, Channel *channel, const char *code, const char *msg)
{
    for (int i = 0; i < client->channel_size; ++i)
    {
        if (!channel || client->channels[i] == channel)
        {
            for (int j = 0; j < client->channels[i]->client_size; ++j)
            {
                if (client->channels[i]->clients[i] != client)
                {
                    write_client_socket(client->channels[i]->clients[i]->sock,
                                        client, code, msg);
                }
            }
        }
    }
}

bool        irc_nick(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    if (!arg || !arg[0] || replace((char *)arg[0], '\n', '\0')[0] == 0)
    {
        write_server_socket(client, ERR_NONICKNAMEGIVEN, "ERR_NONICKNAMEGIVEN");
        return (false);
    }
    if (arg[0][0] == '&' || arg[0][0] == '#')
    {
        write_server_socket(client, ERR_ERRONEUSNICKNAME, "ERR_ERRONEUSNICKNAME");
        return (false);
    }
    if (getClient(manager, arg[0]))
    {
        write_server_socket(client, ERR_NICKNAMEINUSE, "ERR_NICKNAMEINUSE");
        return (false);
    }
    if (client->username)
        client->username = strdup(arg[0]);
    send_msg_to_all(client, NULL, "NICK", client->username);
    return (true);
}

bool        irc_user(Manager *manager, Client *client, const char **arg)
{
    if (client->reg)
    {
        write_server_socket(client, ERR_ALREADYREGISTERED, "ERR_ALREADYREGISTERED");
        return (false);
    }
    if (!arg[0] || !arg[1] || !arg[2] || !arg[3])
    {
        write_server_socket(client, ERR_NEEDMOREPARAMS, "ERR_NEEDMOREPARAMS");
        return (false);
    }
    write_server_socket(client, "001", ":"WELCOME);
    client->reg = concat(3, arg[0], "@", arg[2]);
    (void)manager;
    return (true);
}

bool        irc_list(Manager *manager, Client *client, const char **arg)
{
    char    buffer[BUFF_SIZE];

    write_server_socket(client, RPL_LISTSTART, "Channel :Users  Name");
    for (int i = 0; i < manager->channel_size; ++i)
    {
        memset(buffer, 0, BUFF_SIZE);
        sprintf(buffer, ":%s %d : ", manager->channels[i].name,
                manager->channels[i].client_size);
        write_server_socket(client, RPL_LIST, buffer);
    }
    write_server_socket(client, RPL_LISTEND, ":End of /LIST");
    (void)arg;
    return (true);
}

bool        irc_join(Manager *manager, Client *client, const char **arg)
{
    Channel *channel;

    if (!arg || !arg[0])
    {
        write_server_socket(client, ERR_NEEDMOREPARAMS, "ERR_NEEDMOREPARAMS");
        return (false);
    }
    if (strlen(arg[0]) > 200 || (arg[0][0] != '&' && arg[0][0] != '#'))
    {
        write_server_socket(client, ERR_NOSUCHCHANNEL, "ERR_NOSUCHCHANNEL");
        return (false);
    }
    if (!(channel = getChannel(manager->channels, manager->channel_size, arg[0])))
        channel = new_channel(manager, arg[0]);
    join_channel(client, channel);
    send_msg_to_all(client, NULL, "JOIN", channel->name);
    write_client_socket(client->sock, client, "JOIN", channel->name);
    return (true);
}

bool        irc_part(Manager *manager, Client *client, const char **arg)
{
    Channel *channel;

    if (!(channel = getChannel(manager->channels, manager->channel_size, arg[0])))
        write_server_socket(client, ERR_NOTONCHANNEL, "ERR_NOTONCHANNEL");
    send_msg_to_all(client, NULL, "PART", channel->name);
    write_client_socket(client->sock, client, "PART", channel->name);
    part_channel(client, channel);
    return (true);
}

bool        irc_users(Manager *manager, Client *client, const char **arg)
{
    write_server_socket(client, RPL_USERSSTART, ":UserID Terminal Host");
    if (manager->client_size == 0)
        write_server_socket(client, RPL_NOUSERS, ":Nobody logged in");
    else
    {
        for (int i = 0; i < manager->client_size; ++i)
        {
            write_server_socket(client, RPL_USERS, ":");
        }
    }
    write_server_socket(client, RPL_ENDOFUSERS, ":End of users");
    (void)arg;
    return (true);
}

bool        irc_names(Manager *manager, Client *client, const char **arg)
{
    Channel *channel;
    char    *buffer;
    char    *tmp;

    if (arg[0])
    {
        if ((channel = getChannel(manager->channels, manager->client_size, arg[0])))
        {
            buffer = NULL;
            for (int i = 0; i < manager->client_size; ++i)
            {
                tmp = buffer;
                buffer = concat(3, buffer, " ", manager->clients[i]);
                free(tmp);
            }
            write_server_socket(client, RPL_NAMREPLY, buffer);
        }
    }
    buffer = concat(2, channel->name, " :End of /NAMES list");
    write_server_socket(client, RPL_ENDOFNAMES, buffer);
    free(buffer);
    return (true);
}

bool        irc_msg(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;
    Channel *channel;
    Client  *client_dest;

    if (!arg[0])
        return (write_server_socket(client, ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"), false);
    if (!arg[1])
        return (write_server_socket(client, ERR_NOTEXTTOSEND, ":No text to send"), false);
    buffer = concat(3, arg[0], " : ", arg[1]);
    if (arg[0][0] == '#' || arg[0][0] == '&')
    {
        if (!(channel = getChannel(manager->channels, manager->channel_size, arg[0])))
            return (free(buffer), write_socket(client->sock, ERR_NOSUCHNICK), false);
        send_msg_to_all(client, channel, "PRIVMSG", buffer);
    }
    else
    {
        if (!(client_dest = getClient(manager, arg[0])))
            return (free(buffer), write_socket(client->sock, ERR_NOSUCHNICK), false);
        write_client_socket(client_dest->sock, client, "PRIVMSG", arg[1]);
    }
    free(buffer);
    return (true);
}

bool        irc_quit(Manager *manager, Client *client, const char **arg)
{
    write_socket(client->sock, "QUIT:");
    send_msg_to_all(client, NULL, "QUIT", client->username);
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
