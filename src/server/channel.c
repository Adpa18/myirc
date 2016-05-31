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
#include <stdio.h>
#include "error.h"
#include "server.h"

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
    write_server_socket(client, RPL_LISTEND, "End of /LIST");
    (void)arg;
    return (true);
}

bool        irc_join(Manager *manager, Client *client, const char **arg)
{
    Channel *channel;

    if (!arg || !arg[0])
    {
        write_server_socket(client, ERR_NEEDMOREPARAMS, " :ERR_NEEDMOREPARAMS");
        return (false);
    }
    if (strlen(arg[0]) > 200 || (arg[0][0] != '&' && arg[0][0] != '#'))
    {
        write_server_socket(client, ERR_NOSUCHCHANNEL, " :ERR_NOSUCHCHANNEL");
        return (false);
    }
    if (!(channel = getChannel(manager->channels,
                               manager->channel_size, arg[0])))
        channel = new_channel(manager, arg[0]);
    join_channel(client, channel);
    send_msg_to_all(client, channel, "JOIN", channel->name);
    write_client_socket(client->sock, client, "JOIN", channel->name);
    return (true);
}

bool        irc_part(Manager *manager, Client *client, const char **arg)
{
    Channel *channel;

    if (!(channel = getChannel(manager->channels,
                               manager->channel_size, arg[0])))
    {
        write_server_socket(client, ERR_NOTONCHANNEL, " :ERR_NOTONCHANNEL");
        return (false);
    }
    send_msg_to_all(client, NULL, "PART", channel->name);
    write_client_socket(client->sock, client, "PART", channel->name);
    part_channel(client, channel);
    return (true);
}
