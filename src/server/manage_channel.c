/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:11:49 2016 Adrien WERY
*/

#include <string.h>
#include <server.h>
#include "server.h"

Channel *getChannel(Channel *channels, int size, const char *channel_str)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(channels[i].name, channel_str) == 0)
        {
            return (&channels[i]);
        }
    }
    return (NULL);
}

Channel *new_channel(Manager *manager, const char *channel_str)
{
    Channel *channel;

    channel = &manager->channels[manager->channel_size];
    strncpy(channel->name, channel_str, 200);
    channel->id = manager->channel_size;
    channel->client_size = 0;
    ++manager->channel_size;
    return (channel);
}

void    remove_channel(Manager *manager, int to_remove)
{
    memset(manager->channels[to_remove].name, 0, 200);
    memmove(manager->channels + to_remove, manager->channels + to_remove + 1,
            (manager->channel_size - to_remove - 1) * sizeof(Channel));
    --manager->channel_size;
}

void    join_channel(Client *client, Channel *channel)
{
    for (int i = 0; i < client->channel_size; ++i)
    {
        if (client->channels[i] == channel)
            return;
    }
    client->channels[client->channel_size] = channel;
    channel->clients[channel->client_size] = client;
    ++client->channel_size;
    ++channel->client_size;
}

void    part_channel(Client *client, Channel *channel)
{
    for (int i = 0; i < client->channel_size; ++i)
    {
        if (client->channels[i] == channel)
        {
            memmove(client->channels + i, client->channels + i + 1,
                    (client->channel_size - i - 1) * sizeof(Channel *));
            --client->channel_size;
        }
    }
    for (int i = 0; i < channel->client_size; ++i)
    {
        if (channel->clients[i] == client)
        {
            memmove(channel->clients + i, channel->clients + i + 1,
                    (channel->client_size - i - 1) * sizeof(Client *));
            --channel->client_size;
        }
    }
    client->channels[client->channel_size] = NULL;
    channel->clients[channel->client_size] = NULL;
}