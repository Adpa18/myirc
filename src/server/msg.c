/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:11:09 2016 Adrien WERY
*/

#include <stdlib.h>
#include "error.h"
#include "server.h"

void    send_msg_to_all(Client *client, Channel *channel, const char *code,
                        const char *msg)
{
    for (int i = 0; i < client->channel_size; ++i)
    {
        if (!channel || client->channels[i] == channel)
        {
            for (int j = 0; j < client->channels[i]->client_size; ++j)
            {
                if (client->channels[i]->clients[j] != client)
                {
                    write_client_socket(client->channels[i]->clients[j]->sock,
                                        client, code, msg);
                }
            }
        }
    }
}

bool        irc_msg(Manager *manager, Client *client, const char **arg)
{
    char    *buffer;
    Channel *channel;
    Client  *client_dest;

    if (!arg[0])
        return (write_server_socket(client, ERR_NORECIPIENT,
                                    " :No recipient given (PRIVMSG)"), false);
    if (!arg[1])
        return (write_server_socket(client, ERR_NOTEXTTOSEND,
                                    " :No text to send"), false);
    buffer = concat(2, "PRIVMSG ", arg[0]);
    if (arg[0][0] == '#' || arg[0][0] == '&')
    {
        if (!(channel = getChannel(manager->channels,
                                   manager->channel_size, arg[0])))
            return (free(buffer), write_socket(client->sock, ERR_NOSUCHNICK),
                    false);
        send_msg_to_all(client, channel, buffer, arg[1]);
    }
    else if (!(client_dest = getClient(manager, arg[0])))
        return (free(buffer), write_socket(client->sock, ERR_NOSUCHNICK),
                false);
    else
        write_client_socket(client_dest->sock, client, buffer, arg[1]);
    return (free(buffer), true);
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
