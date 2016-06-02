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
#include "cmd_server.h"
#include "array.h"

bool    handle_cmds(Manager *manager, Client *client, const char *cmd_line)
{
    char    **array;

    if (cmd_line[0] == '\n')
        return (false);
    array = split(cmd_line, "\r\n");
    for (int i = 0; i < array_len((const char **)array); ++i)
    {
        DEBUG("cmd = %s\n", array[i]);
        handle_cmd(manager, client, array[i]);
    }
    free_array(array);
    return (true);
}

bool    handle_cmd(Manager *manager, Client *client, const char *cmd_line)
{
    char    **array;
    bool    ret;

    if (cmd_line[0] == '\n')
        return (false);
    array = split(cmd_line, " ");
    for (unsigned  int i = 0; i < sizeof(cmdlist_str) / sizeof(char *); ++i)
    {
        if (strcasecmp(array[0], cmdlist_str[i]))
            continue;
        if (client->reg || i == NICK || i == USER || i == QUIT)
            ret = cmdlist_func[i](manager, client, (const char **)(&array[1]));
        else
        {
            write_server_socket(client, ERR_NOTREGISTERED,
                                " :You have not registered");
            ret = false;
        }

        free_array(array);
        return (ret);
    }
    write_server_socket(client, ERR_UNKNOWCMD, " :Unknown CMD");
    return (free_array(array), true);
}