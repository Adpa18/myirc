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

bool    irc_msg(t_client *cl, const char **arg)
{
    char    *buffer;

    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    buffer = merge(arg, " ");
    send_cmd(cl->sock, "PRIVMSG ", buffer);
    free(buffer);
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