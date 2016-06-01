/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:10:10 2016 Adrien WERY
*/

#include "socket.h"
#include "cmd_list_client.h"
#include "array.h"

extern bool killed;

bool    irc_nick(t_client *cl, const char **arg)
{
    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    send_cmd(cl->sock, "NICK", arg[0]);
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
    buffer = merge(arg, " ");
    send_cmd(cl->sock, "USER", buffer);
    free(buffer);
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
    send_cmd(cl->sock, "QUIT", arg[0]);
    killed = true;
    return (true);
}
