/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:10:10 2016 Adrien WERY
*/

#include <socket.h>
#include <arpa/inet.h>
#include <pwd.h>
#include "cmd_list_client.h"
#include "array.h"

extern bool killed;

void    send_cmd(SOCKET sock, const char *cmd, const char *arg)
{
    char    *buffer;

    buffer = concat(3, cmd, arg, CRLF);
    write_socket(sock, buffer);
    free(buffer);
}

void    init_connection(t_client *cl)
{
    struct passwd   *pw;
    char            *buffer;

    pw = getUser();
    send_cmd(cl->sock, "NICK ", pw->pw_name);
    buffer = concat(4, pw->pw_name, " 0 * :", pw->pw_gecos, CRLF);
    send_cmd(cl->sock, "USER ", buffer);
    DEBUG("%s\n", buffer);
    free(buffer);
}

bool    irc_server(t_client *cl, const char **arg)
{
    SOCKADDR_IN     s_in;
    struct timeval  t;
    char            **array;

    if (!(array = split(arg[0], " ")) || !array[0] || !array[1])
        return (free_array(array), false);
    t.tv_sec = 30;
    t.tv_usec = 0;
    if ((cl->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return (false);
    }
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(atoi(array[1]));
    s_in.sin_addr.s_addr = inet_addr(array[0]);
    setsockopt(cl->sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&t, sizeof(t));
    if (connect(cl->sock, (SOCKADDR *)&s_in, sizeof(s_in)) == -1)
        return (perror("conect"), false);
    cl->max_fd = cl->sock > cl->max_fd ? cl->sock : cl->max_fd;
    cl->isConnected = true;
    init_connection(cl);
    return (true);
}

bool    irc_nick(t_client *cl, const char **arg)
{
    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    send_cmd(cl->sock, "NICK ", arg[0]);
    return (true);
}

bool    irc_user(t_client *cl, const char **arg)
{
    char    *buffer;

    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    buffer = merge(arg, ' ');
    send_cmd(cl->sock, "USER ", buffer);
    free(buffer);
    return (true);
}

bool    irc_list(t_client *cl, const char **arg)
{
    (void)cl;
    (void)arg;
    return (true);
}


bool    irc_join(t_client *cl, const char **arg)
{
    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    send_cmd(cl->sock, "JOIN ", arg[0]);
    return (true);
}

bool    irc_part(t_client *cl, const char **arg)
{
    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    send_cmd(cl->sock, "PART ", arg[0]);
    return (true);
}

bool    irc_users(t_client *cl, const char **arg)
{
    (void)arg;
    send_cmd(cl->sock, "USERS", 0);
    return (true);
}

bool    irc_send_file(t_client *cl, const char **arg)
{
    (void)cl;
    (void)arg;
    return (true);
}

bool    irc_accept_file(t_client *cl, const char **arg)
{
    (void)cl;
    (void)arg;
    return (true);
}

bool    irc_help(t_client *cl, const char **arg)
{
    (void)cl;
    (void)arg;
    return (true);
}

bool    irc_quit(t_client *cl, const char **arg)
{
    send_cmd(cl->sock, "QUIT ", arg[0]);
    killed = true;
    return (true);
}
