/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef PSU_2015_MYIRC_SERVER_H
# define PSU_2015_MYIRC_SERVER_H

# include "common.h"
# include "socket.h"

# define USAGE          "./server [port]\n"
# define MAX_CLIENTS    42
# define MAX_CHANNELS   42
# define NICK_PREFIX    "Guest"
# define EOT_CLIENT     "Client %d is disconnected !\n"
# define KILL_SIGINT    "Server was kiled by SIGINT\n"

# define WELCOME        "Welcome to my house"
# define ERROR_MAX      "Sorry, the maximum number of connections"CRLF

typedef struct Client   Client;
typedef struct Channel  Channel;

struct Client
{
    unsigned int    id;
    SOCKET          sock;
    char            *reg;
    char            *username;
    Channel         *channels[MAX_CHANNELS];
    int             channel_size;
};

struct Channel
{
    unsigned int    id;
    char            name[200];
    Client          *clients[MAX_CLIENTS];
    int             client_size;
};

typedef struct
{
    Client  clients[MAX_CLIENTS * MAX_CHANNELS];
    Channel channels[MAX_CHANNELS * MAX_CLIENTS];
    int     client_size;
    int     channel_size;
    int     max_fd;
}           Manager;

bool        new_client(SOCKET sock, fd_set *rdfs, Manager *manager);
void        remove_client(Manager *manager, int to_remove);
void        listen_clients(fd_set *rdfs, Manager *manager);
Client      *getClient(Manager *manager, const char *client_str);
Channel     *new_channel(Manager *manager, const char *channel_str);
void        remove_channel(Manager *manager, int to_remove);
Channel     *getChannel(Channel *channels, int size, const char *channel_str);
void        join_channel(Client *client, Channel *channel);
void        part_channel(Client *client, Channel *channel);
bool        handle_cmds(Manager *manager, Client *client, const char *cmd_line);
bool        handle_cmd(Manager *manager, Client *client, const char *cmd_line);
void        send_msg_to_all(Client *client, Channel *channel, const char *code, const char *msg);

#endif //PSU_2015_MYIRC_SERVER_H
