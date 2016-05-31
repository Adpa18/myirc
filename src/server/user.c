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
#include "error.h"
#include "server.h"

bool        irc_nick(Manager *manager, Client *client, const char **arg)
{
    (void)manager;
    if (!arg || !arg[0] || replace((char *)arg[0], '\n', '\0')[0] == 0)
    {
        write_server_socket(client, ERR_NONICKNAMEGIVEN,
                            " :ERR_NONICKNAMEGIVEN");
        return (false);
    }
    if (arg[0][0] == '&' || arg[0][0] == '#')
    {
        write_server_socket(client, ERR_ERRONEUSNICKNAME,
                            " :ERR_ERRONEUSNICKNAME");
        return (false);
    }
    if (getClient(manager, arg[0]))
    {
        write_server_socket(client, ERR_NICKNAMEINUSE,
                            " :ERR_NICKNAMEINUSE");
        return (false);
    }
    if (client->username)
        free(client->username);
    client->username = strdup(arg[0]);
    send_msg_to_all(client, NULL, "NICK", client->username);
    return (true);
}

bool        irc_user(Manager *manager, Client *client, const char **arg)
{
    if (client->reg)
    {
        write_server_socket(client, ERR_ALREADYREGISTERED,
                            " :ERR_ALREADYREGISTERED");
        return (false);
    }
    if (!arg[0] || !arg[1] || !arg[2] || !arg[3])
    {
        write_server_socket(client, ERR_NEEDMOREPARAMS,
                            " :ERR_NEEDMOREPARAMS");
        return (false);
    }
    write_server_socket(client, "001", " :"WELCOME);
    client->reg = concat(3, arg[0], "@", arg[2]);
    (void)manager;
    return (true);
}

bool        irc_users(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;

    write_server_socket(client, RPL_USERSSTART, " :UserID Terminal Host");
    if (manager->client_size == 0)
        write_server_socket(client, RPL_NOUSERS, " :Nobody logged in");
    else
    {
        for (int i = 0; i < manager->client_size; ++i)
        {
            buffer = concat(2, " :", manager->clients[i].username);
            write_server_socket(client, RPL_USERS, buffer);
            free(buffer);
        }
    }
    write_server_socket(client, RPL_ENDOFUSERS, " :End of users");
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
        if ((channel = getChannel(manager->channels,
                                  manager->client_size, arg[0])))
        {
            buffer = concat(3, " = ", channel->name, " :");
            for (int i = 0; i < manager->client_size; ++i)
            {
                tmp = buffer;
                buffer = concat(3, buffer, manager->clients[i].username, " ");
                free(tmp);
            }
            write_server_socket(client, RPL_NAMREPLY, buffer);
        }
    }
    buffer = concat(3, " ", (channel) ? channel->name : "*",
                    " :End of /NAMES list");
    write_server_socket(client, RPL_ENDOFNAMES, buffer);
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