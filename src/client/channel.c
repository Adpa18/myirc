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

bool    irc_list(t_client *cl, const char **arg)
{
    send_cmd(cl->sock, "LIST", NULL);
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
    send_cmd(cl->sock, "JOIN", arg[0]);
    return (true);
}

bool    irc_part(t_client *cl, const char **arg)
{
    if (!arg || !arg[0])
    {
        write_socket(STDOUT_FILENO, INVALID_ARG);
        return (false);
    }
    send_cmd(cl->sock, "PART", arg[0]);
    return (true);
}

bool    irc_users(t_client *cl, const char **arg)
{
    (void)arg;
    send_cmd(cl->sock, "USERS", NULL);
    return (true);
}

bool    irc_names(t_client *cl, const char **arg)
{
    (void)arg;
    send_cmd(cl->sock, "NAMES", NULL);
    return (true);
}
