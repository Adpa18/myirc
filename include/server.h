//
// Created by wery_a on 15/05/16.
//

#ifndef PSU_2015_MYIRC_SERVER_H
# define PSU_2015_MYIRC_SERVER_H

# include "common.h"
# include "socket.h"

# define USAGE          "./server [port]\n"
# define MAX_CLIENTS    42
# define NICK_PREFIX    "Guest"
# define EOT_CLIENT     "Client %d is disconnected !\n"
# define KILL_SIGINT    "Server was kiled by SIGINT\n"

# define CRLF           "\r\n\0"
# define WELCOME        "Welcome to my house : "
# define ERROR_MAX      "Sorry, the maximum number of connections"CRLF

typedef struct
{
    SOCKET      sock;
    char        *username;
    char        channel[200];
}               Client;

typedef struct
{
    Client  clients[MAX_CLIENTS];
    int     size;
    int     max_fd;
}           Manager;

bool        new_client(SOCKET sock, fd_set *rdfs, Manager *manager);
void        remove_client(Manager *manager, int to_remove);
void        listen_clients(fd_set *rdfs, Manager *manager);
bool        handle_cmd(Manager *manager, Client *client, const char *cmd_line);
void        send_msg_to_all(Manager *manager, Client *client, const char *msg, bool himself);

#endif //PSU_2015_MYIRC_SERVER_H
