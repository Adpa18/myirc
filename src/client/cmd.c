/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Sun Jun 05 16:08:06 2016 Axel Vencatareddy
*/

#include <socket.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <string.h>
#include "cmd_client.h"
#include "array.h"

extern bool killed;

COMMAND getCMD(const char *cmd_line)
{
    if (cmd_line[0] == '\n')
        return (false);
    for (unsigned  int i = 0; i < sizeof(cmdlist_str) / sizeof(char *); ++i)
    {
        if (strcasecmp(cmd_line, cmdlist_str[i]) == 0)
        {
            return (i);
        }
    }
    return (NO_CMD);
}

bool  handle_cmd(t_client *cl)
{
    COMMAND   cmd;
    char      **array;
    char      *buffer;
    bool      ret;

    ret = true;
    if ((buffer = read_socket(0)) == NULL || buffer[0] == '\n')
        return (false);
    if ((array = split(buffer, " ")) == NULL)
        return (false);
    if ((cmd = getCMD(array[0])) == NO_CMD && cl->isConnected)
        write_socket(cl->sock, buffer);
    else if (cl->isConnected || cmd == SERVER || cmd == HELP)
        ret = cmdlist_func[cmd](cl, (const char **)&array[1]);
    else
        write_socket(STDOUT_FILENO, NEED_CO);
    free(buffer);
    return (ret);
}

void    send_cmd(SOCKET sock, const char *cmd, const char *arg)
{
    char    *buffer;

    if (arg)
        buffer = concat(4, cmd, " ", arg, CRLF);
    else
        buffer = concat(2, cmd, CRLF);
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
  char            *buffer;
  struct timeval  t;
  char            **tab;

  t.tv_sec = 30;
  t.tv_usec = 0;
  if ((cl->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (perror("socket"), false);
  tab = split(arg[0], ":");
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(tab[1] ? atoi(tab[1]) :
                        (arg[1] ? atoi(arg[1]) : 6667));
  s_in.sin_addr.s_addr = inet_addr(getIP(tab[0]));
  setsockopt(cl->sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&t, sizeof(t));
  if (connect(cl->sock, (SOCKADDR *)&s_in, sizeof(s_in)) == -1)
      return (perror("conect"), false);
  cl->max_fd = cl->sock > cl->max_fd ? cl->sock : cl->max_fd;
  cl->isConnected = true;
  init_connection(cl);
  buffer = concat(3, "Connected to ", tab[0], "\n");
  write_socket(STDOUT_FILENO, buffer);
  free_array(tab);
  free(buffer);
  return (true);
}
